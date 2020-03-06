#include "h264.h"

namespace cafe::h264
{

static int32_t
rpl_entry(coreinit::OSDynLoad_ModuleHandle moduleHandle,
          coreinit::OSDynLoad_EntryReason reason)
{
   return 0;
}

void
Library::registerSymbols()
{
   RegisterEntryPoint(rpl_entry);

   registerDecodeSymbols();
   registerStreamSymbols();
}

} // namespace cafe::h264
