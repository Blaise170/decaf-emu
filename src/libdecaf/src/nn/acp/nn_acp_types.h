#pragma once
#include <libcpu/be2_struct.h>

namespace nn::acp
{

struct ACPMetaXml
{
   UNKNOWN(0x3440);
};
CHECK_SIZE(ACPMetaXml, 0x3440);

} // namespace nn::acp
