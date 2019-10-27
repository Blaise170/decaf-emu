#pragma once
#include <libcpu/be2_struct.h>

namespace nn::ipc
{

struct ManagedBuffer
{
   ManagedBuffer(bool input, bool output) :
      input(input),
      output(output)
   {
   }

   ManagedBuffer(virt_ptr<void> ptr,
                 uint32_t size,
                 bool input,
                 bool output) :
      ptr(ptr),
      size(size),
      input(input),
      output(output)
   {
   }

   uint32_t totalSize()
   {
      return unalignedBeforeBufferSize + alignedBufferSize + unalignedAfterBufferSize;
   }

   void writeOutput(phys_ptr<void> data, uint32_t size)
   {
      writeOutput(data.get(), size);
   }

   void writeOutput(const void *data, size_t size)
   {
      auto ptr = reinterpret_cast<const uint8_t *>(data);

      if (unalignedBeforeBufferSize && size) {
         auto count = std::min<size_t>(unalignedBeforeBufferSize, size);
         std::memcpy(unalignedBeforeBuffer.get(), ptr, count);
         ptr += size;
         size -= count;
      }

      if (alignedBufferSize && size) {
         auto count = std::min<size_t>(alignedBufferSize, size);
         std::memcpy(alignedBuffer.get(), ptr, count);
         ptr += size;
         size -= count;
      }

      if (unalignedAfterBufferSize && size) {
         auto count = std::min<size_t>(unalignedAfterBufferSize, size);
         std::memcpy(unalignedAfterBuffer.get(), ptr, count);
         ptr += size;
         size -= count;
      }
   }

   // For serialisation:
   virt_ptr<void> ptr = nullptr;
   uint32_t size = 0u;

   // For deserialisation:
   phys_ptr<void> unalignedBeforeBuffer = nullptr;
   uint32_t unalignedBeforeBufferSize = 0u;

   phys_ptr<void> alignedBuffer = nullptr;
   uint32_t alignedBufferSize = 0u;

   phys_ptr<void> unalignedAfterBuffer = nullptr;
   uint32_t unalignedAfterBufferSize = 0u;

   // For both:
   bool input;
   bool output;
};

template<typename Type>
struct InBuffer : ManagedBuffer
{
   InBuffer() :
      ManagedBuffer(true, false)
   {
   }

   InBuffer(virt_ptr<Type> ptr) :
      ManagedBuffer(ptr, static_cast<uint32_t>(sizeof(Type)), true, false)
   {
   }

   InBuffer(virt_ptr<Type> ptr, uint32_t count) :
      ManagedBuffer(ptr, static_cast<uint32_t>(sizeof(Type) * count), true, false)
   {
   }
};

template<>
struct InBuffer<void> : ManagedBuffer
{
   InBuffer() :
      ManagedBuffer(true, false)
   {
   }

   InBuffer(virt_ptr<void> ptr, uint32_t count) :
      ManagedBuffer(ptr, count, true, false)
   {
   }
};

template<typename Type>
struct InOutBuffer : ManagedBuffer
{
   InOutBuffer() :
      ManagedBuffer(true, true)
   {
   }

   InOutBuffer(virt_ptr<Type> ptr) :
      ManagedBuffer(ptr, static_cast<uint32_t>(sizeof(Type)), true, true)
   {
   }

   InOutBuffer(virt_ptr<Type> ptr, uint32_t count) :
      ManagedBuffer(ptr, static_cast<uint32_t>(sizeof(Type) * count), true, true)
   {
   }
};

template<>
struct InOutBuffer<void> : ManagedBuffer
{
   InOutBuffer() :
      ManagedBuffer(true, true)
   {
   }

   InOutBuffer(virt_ptr<void> ptr, uint32_t count) :
      ManagedBuffer(ptr, count, true, true)
   {
   }
};

template<typename Type>
struct OutBuffer : ManagedBuffer
{
   OutBuffer() :
      ManagedBuffer(false, true)
   {
   }

   OutBuffer(virt_ptr<Type> ptr) :
      ManagedBuffer(ptr, static_cast<uint32_t>(sizeof(Type)), false, true)
   {
   }

   OutBuffer(virt_ptr<Type> ptr, uint32_t count) :
      ManagedBuffer(ptr, static_cast<uint32_t>(sizeof(Type) * count), false, true)
   {
   }
};

template<>
struct OutBuffer<void> : ManagedBuffer
{
   OutBuffer() :
      ManagedBuffer(false, true)
   {
   }

   OutBuffer(virt_ptr<void> ptr, uint32_t count) :
      ManagedBuffer(ptr, count, false, true)
   {
   }
};

} // namespace nn::ipc
