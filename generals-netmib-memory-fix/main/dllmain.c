#include <windows.h>

#include "../init.h"

DWORD 
WINAPI 
EntryThread(LPVOID parameter) {
  netmib_fix_init();

  return 0;
}

BOOL 
WINAPI 
DllMain(HINSTANCE dll, DWORD reason, LPVOID reserved) {
  switch (reason) {
    case(DLL_PROCESS_ATTACH): {
      DisableThreadLibraryCalls(dll);
      CreateThread(NULL, 0, &EntryThread, (LPVOID)dll, NULL, 0);

      break;
    }
    case(DLL_PROCESS_DETACH): {
      break;
    }
  }

  return TRUE;
}
