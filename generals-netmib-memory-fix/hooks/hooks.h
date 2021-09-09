#ifndef HOOKS_H
#define HOOKS_H

#include <windows.h>
#include <snmp.h>

#include "../detour/detour.h"

/*     ===
SnmpExtensionQuery
       ===      */

typedef BOOL(SNMP_FUNC_TYPE *t_SnmpExtensionQuery)(
  BYTE bPduType,
  SnmpVarBindList* pVarBindList,
  AsnInteger32* pErrorStatus,
  AsnInteger32* pErrorIndex
);

extern detour_t *d_SnmpExtensionQuery;

BOOL 
SNMP_FUNC_TYPE 
h_SnmpExtensionQuery(
  BYTE bPduType,
  SnmpVarBindList *pVarBindList,
  AsnInteger32 *pErrorStatus,
  AsnInteger32 *pErrorIndex
);

/*     ===
==================
       ===      */

#endif
