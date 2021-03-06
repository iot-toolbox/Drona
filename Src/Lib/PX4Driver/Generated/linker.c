
  #include "linker.h"
  PRT_FUNDECL P_FUN_IGNORE_PUSH_STRUCT = 
  {
    _P_FUN_PUSH_OR_IGN,
    0U,
    NULL,
    NULL,
    1U,
    0U,
    0U,
    NULL,
    NULL,
    0U,
    NULL,
    0U,
    NULL
  };
  PRT_FOREIGNTYPEDECL P_GEND_FOREIGNTYPES[] = 
  {
    
    {
        P_FORGN_TYPE_float32,
        "float32",
        &PRT_FORGN_MKDEF_float32_IMPL,
        &PRT_FORGN_CLONE_float32_IMPL,
        &PRT_FORGN_FREE_float32_IMPL,
        &PRT_FORGN_GETHASHCODE_float32_IMPL,
        &PRT_FORGN_ISEQUAL_float32_IMPL,
        &PRT_FORGN_TOSTRING_float32_IMPL,
        0U,
        NULL
    }
  };
  PRT_EVENTDECL *P_GEND_EVENTS[] = 
  {
    &_P_EVENT_NULL_STRUCT,
    &_P_EVENT_HALT_STRUCT
  };
  PRT_FUNDECL *P_GEND_FUNS[] = 
  {
    &P_FUN_IGNORE_PUSH_STRUCT,
    &P_FUN_AbsFloat32_STRUCT,
    &P_FUN_AddFloat32_STRUCT,
    &P_FUN_DivFloat32_STRUCT,
    &P_FUN_IntToFloat32_STRUCT,
    &P_FUN_IsEqFloat32_STRUCT,
    &P_FUN_IsFiniteFloat32_STRUCT,
    &P_FUN_IsGeFloat32_STRUCT,
    &P_FUN_IsGtFloat32_STRUCT,
    &P_FUN_IsInftyFloat32_STRUCT,
    &P_FUN_IsLeFloat32_STRUCT,
    &P_FUN_IsLtFloat32_STRUCT,
    &P_FUN_IsNEqFloat32_STRUCT,
    &P_FUN_IsNaNFloat32_STRUCT,
    &P_FUN_IsNearFloat32_STRUCT,
    &P_FUN_IsNegInftyFloat32_STRUCT,
    &P_FUN_IsPosInftyFloat32_STRUCT,
    &P_FUN_MulFloat32_STRUCT,
    &P_FUN_NaNFloat32_STRUCT,
    &P_FUN_NegFloat32_STRUCT,
    &P_FUN_ScientificToFloat32_STRUCT,
    &P_FUN_SubFloat32_STRUCT
  };
  PRT_PROGRAMDECL P_GEND_PROGRAM = 
  {
    2U,
    0U,
    0U,
    22U,
    1U,
    P_GEND_EVENTS,
    NULL,
    NULL,
    P_GEND_FUNS,
    P_GEND_FOREIGNTYPES,
    NULL,
    NULL,
    0U,
    NULL
  };
  