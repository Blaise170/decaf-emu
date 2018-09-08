#pragma once
#include "cafe_kernel_context.h"
#include <libcpu/be2_struct.h>
#include <libcpu/cpu.h>

namespace cafe::kernel
{

#include <common/enum_start.h>

ENUM_BEG(ExceptionType, uint32_t)
   ENUM_VALUE(SystemReset, 0)
   ENUM_VALUE(MachineCheck, 1)
   ENUM_VALUE(DSI, 2)
   ENUM_VALUE(ISI, 3)
   ENUM_VALUE(ExternalInterrupt, 4)
   ENUM_VALUE(Alignment, 5)
   ENUM_VALUE(Program, 6)
   ENUM_VALUE(FloatingPoint, 7)
   ENUM_VALUE(Decrementer, 8)
   ENUM_VALUE(SystemCall, 9)
   ENUM_VALUE(Trace, 10)
   ENUM_VALUE(PerformanceMonitor, 11)
   ENUM_VALUE(Breakpoint, 12)
   ENUM_VALUE(SystemInterrupt, 13)
   ENUM_VALUE(ICI, 14)
   ENUM_VALUE(Max, 15)
ENUM_END(ExceptionType)

#include <common/enum_end.h>

namespace internal
{

void
initialiseExceptionContext(cpu::Core *core);

void
initialiseExceptionHandlers();

void
initialiseStaticExceptionData();

} // namespace internal

} // namespace cafe::kernel
