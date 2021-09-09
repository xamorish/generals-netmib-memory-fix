#include "init.h"

#include <windows.h>

#include "detour/detour.h"
#include "hooks/hooks.h"

static void
netmib_fix_apply_hooks() {
  HMODULE inetmib1 = GetModuleHandleA("inetmib1.dll");
  if (inetmib1 == NULL) {
    // The game loads it later on anyway. :>
    inetmib1 = LoadLibraryA("inetmib1.dll");
  }

  uintptr_t p_SnmpExtensionQuery = (uintptr_t)(GetProcAddress(inetmib1, "SnmpExtensionQuery"));
  d_SnmpExtensionQuery = detour_attach(p_SnmpExtensionQuery, h_SnmpExtensionQuery, 5);
}

int
netmib_fix_init() {
  netmib_fix_apply_hooks();

  return 0;
}
