#include "hooks.h"

/*     ===
SnmpExtensionQuery
       ===      */

detour_t *d_SnmpExtensionQuery = (detour_t*)0;

BOOL
SNMP_FUNC_TYPE
h_SnmpExtensionQuery(
  BYTE bPduType,
  SnmpVarBindList* pVarBindList,
  AsnInteger32* pErrorStatus,
  AsnInteger32* pErrorIndex
) {
  return ((t_SnmpExtensionQuery)(d_SnmpExtensionQuery->gateway))(bPduType, pVarBindList, pErrorStatus, pErrorIndex);
}

/*     ===
==================
       ===      */
