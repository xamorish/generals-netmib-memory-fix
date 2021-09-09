#include "detour.h"

#include <windows.h>
#include <malloc.h>

#define SIZE_OF_JMP_OPCODE (sizeof(unsigned char))
#define SIZE_OF_ADDRESS (sizeof(uintptr_t))
#define SIZE_OF_RELJUMP_OPERATION (SIZE_OF_JMP_OPCODE + SIZE_OF_ADDRESS)

#define JMP_OPCODE_BYTE ((unsigned char)'\xE9')
#define NOP_OPCODE_BYTE ((unsigned char)'\x90')

#define CALCULATE_RELJUMP_ADDRESS(from, to) ((to) - (from) - SIZE_OF_RELJUMP_OPERATION)

static void
detour_put_reljump(uintptr_t from, uintptr_t to) {
  *(unsigned char*)(from) = JMP_OPCODE_BYTE;
  *(uintptr_t*)(from + SIZE_OF_JMP_OPCODE) = CALCULATE_RELJUMP_ADDRESS(from, to);
}

detour_t*
detour_attach(uintptr_t original, uintptr_t hook, size_t size_of_stolen_code) {
  // Create the gateway.
  uintptr_t size_of_gateway = size_of_stolen_code + SIZE_OF_RELJUMP_OPERATION;
  uintptr_t gateway = (uintptr_t)malloc(size_of_gateway);

  DWORD old_protection;
  VirtualProtect(gateway, size_of_gateway, PAGE_EXECUTE_READWRITE, &old_protection);

  // Steal the code from the original for the gateway.
  memcpy(gateway, original, size_of_stolen_code);

  // Make the gateway call the original.
  detour_put_reljump(gateway, (original + size_of_stolen_code));
  
  // Make the original call the hook.
  VirtualProtect(original, size_of_stolen_code, PAGE_EXECUTE_READWRITE, &old_protection);

  memset(original, NOP_OPCODE_BYTE, size_of_stolen_code);
  detour_put_reljump(original, hook);

  VirtualProtect(original, size_of_stolen_code, old_protection, &old_protection);

  // Return the data.
  detour_t *detour = (detour_t*)malloc(sizeof(detour_t));
  detour->original = original;
  detour->gateway = gateway;
  detour->hook = hook;
  detour->size_of_stolen_code = size_of_stolen_code;

  return detour;
}

int
detour_detach(detour_t* detour) {
  if (detour == (detour_t*)0) {
    return 1;
  }

  // Return the stolen code to the original.
  memcpy(detour->original, detour->gateway, detour->size_of_stolen_code);

  free(detour->gateway);
  free(detour);

  return 0;
}
