#ifndef CAFE_NN_CMPT_ENUM_H
#define CAFE_NN_CMPT_ENUM_H

#include <common/enum_start.inl>

ENUM_NAMESPACE_ENTER(cafe)
ENUM_NAMESPACE_ENTER(nn_cmpt)

ENUM_BEG(CMPTError, int32_t)
   ENUM_VALUE(OK,                0)
   ENUM_VALUE(UserConfigError,   -512)
ENUM_END(CMPTError)

FLAGS_BEG(CMPTPcConfFlags, uint32_t)
   FLAGS_VALUE(None,             0)
   FLAGS_VALUE(RstInternetCh,    1 << 0)
   FLAGS_VALUE(RstNwAccess,      1 << 1)
   FLAGS_VALUE(RstPtOrder,       1 << 2)
FLAGS_END(CMPTPcConfFlags)

ENUM_NAMESPACE_EXIT(nn_cmpt)
ENUM_NAMESPACE_EXIT(cafe)

#include <common/enum_end.inl>

#endif // ifdef CAFE_NN_CMPT_ENUM_H
