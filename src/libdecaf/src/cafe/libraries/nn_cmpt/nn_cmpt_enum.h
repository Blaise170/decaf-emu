#ifndef CAFE_NN_CMPT_ENUM_H
#define CAFE_NN_CMPT_ENUM_H

#include <common/enum_start.h>

ENUM_NAMESPACE_ENTER(cafe)
ENUM_NAMESPACE_ENTER(nn)
ENUM_NAMESPACE_ENTER(cmpt)

ENUM_BEG(CMPTError, int32_t)
   ENUM_VALUE(OK,                0)
ENUM_END(CMPTError)

ENUM_NAMESPACE_EXIT(cmpt)
ENUM_NAMESPACE_EXIT(nn)
ENUM_NAMESPACE_EXIT(cafe)

#include <common/enum_end.h>

#endif // ifdef CAFE_NN_CMPT_ENUM_H
