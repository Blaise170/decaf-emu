#pragma once
#include "ios/ios_enum.h"

#include <cstdint>
#include <libcpu/be2_struct.h>
#include <string_view>
#include <utility>

namespace ios::kernel
{

constexpr auto NumIosProcess = 14;

Error
IOS_GetCurrentProcessId();

Error
IOS_GetProcessName(ProcessId process,
                   char *buffer);

phys_ptr<void>
allocProcessStatic(ProcessId pid,
                   size_t size,
                   size_t align);

phys_ptr<void>
allocProcessLocalHeap(size_t size);

phys_ptr<char>
allocProcessStatic(std::string_view str);

namespace internal
{

ProcessId
getCurrentProcessId();

void
initialiseProcessStaticAllocators();

} // namespace internal

template<typename Type>
inline phys_ptr<Type>
allocProcessStatic()
{
   auto data = allocProcessStatic(internal::getCurrentProcessId(), sizeof(Type), alignof(Type));
   new (data.get()) Type { };
   return phys_cast<Type *>(data);
}

} // namespace ios::kernel
