#include "tcl.h"
#include "tcl_aperture.h"
#include "tcl_driver.h"
#include "tcl_interrupthandler.h"
#include "tcl_ring.h"

namespace cafe::tcl
{

static int32_t
rpl_entry(coreinit::OSDynLoad_ModuleHandle moduleHandle,
          coreinit::OSDynLoad_EntryReason reason)
{
   internal::initialiseTclDriver();
   internal::initialiseApertures();
   internal::initialiseInterruptHandler();
   internal::initialiseRing();
   return 0;
}

void
Library::registerSymbols()
{
   RegisterEntryPoint(rpl_entry);

   registerApertureSymbols();
   registerDriverSymbols();
   registerInterruptHandlerSymbols();
   registerRegisterSymbols();
   registerRingSymbols();
}

} // namespace cafe::tcl
