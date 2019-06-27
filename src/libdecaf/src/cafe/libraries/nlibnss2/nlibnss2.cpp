#include "nlibnss2.h"
#include "cafe/libraries/coreinit/coreinit_dynload.h"

namespace cafe::nlibnss2
{

static int32_t
rpl_entry(coreinit::OSDynLoad_ModuleHandle moduleHandle,
          coreinit::OSDynLoad_EntryReason reason)
{
   coreinit::internal::relocateHleLibrary(moduleHandle);
   return 0;
}

void
Library::registerSymbols()
{
   RegisterEntryPoint(rpl_entry);
}

} // namespace cafe::nlibnss2
