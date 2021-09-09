#ifndef DETOUR_H
#define DETOUR_H

#include <stdint.h>

typedef struct {
  uintptr_t hook;
  uintptr_t gateway;
  uintptr_t original;

  size_t size_of_stolen_code;
} detour_t;

detour_t*
detour_attach(uintptr_t original, uintptr_t hook, size_t size_of_stolen_code);

int
detour_detach(detour_t *detour);

#endif
