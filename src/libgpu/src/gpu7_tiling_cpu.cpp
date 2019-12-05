﻿#include "gpu7_tiling_cpu.h"

#include <common/align.h>
#include <common/decaf_assert.h>

namespace gpu7::tiling::cpu
{

struct MicroTiler8
{
   /*
      8 bits per element:
       0:   0,  1,  2,  3,  4,  5,  6,  7,
       8:  16, 17, 18, 19, 20, 21, 22, 23,
      16:   8,  9, 10, 11, 12, 13, 14, 15,
      24:  24, 25, 26, 27, 28, 29, 30, 31,

      32:  32, 33, 34, 35, 36, 37, 38, 39,
      40:  48, 49, 50, 51, 52, 53, 54, 55,
      48:  40, 41, 42, 43, 44, 45, 46, 47,
      56:  56, 57, 58, 59, 60, 61, 62, 63,
   */

   static inline void
      apply(uint8_t* src,
            int srcOffset,
            int srcStrideBytes,
            uint8_t* dst,
            int dstOffset,
            int dstStrideBytes)
   {
      static constexpr auto rowSize = MicroTileWidth * (8 / 8);
      src += srcOffset;
      dst += dstOffset;

      for (int y = 0; y < MicroTileHeight; y += 4) {
         std::memcpy(dst, src + 0 * srcStrideBytes, rowSize);
         dst += dstStrideBytes;

         std::memcpy(dst, src + 2 * srcStrideBytes, rowSize);
         dst += dstStrideBytes;

         std::memcpy(dst, src + 1 * srcStrideBytes, rowSize);
         dst += dstStrideBytes;

         std::memcpy(dst, src + 3 * srcStrideBytes, rowSize);
         dst += dstStrideBytes;

         src += 4 * srcStrideBytes;
      }
   }
};

struct MicroTiler16
{
   /*
      16 bits per element:
       0:   0,  1,  2,  3,  4,  5,  6,  7,
       8:   8,  9, 10, 11, 12, 13, 14, 15,
      16:  16, 17, 18, 19, 20, 21, 22, 23,
      24:  24, 25, 26, 27, 28, 29, 30, 31,
      32:  32, 33, 34, 35, 36, 37, 38, 39,
      40:  40, 41, 42, 43, 44, 45, 46, 47,
      48:  48, 49, 50, 51, 52, 53, 54, 55,
      56:  56, 57, 58, 59, 60, 61, 62, 63,
   */

   static inline void
      apply(uint8_t* src,
            int srcOffset,
            int srcStrideBytes,
            uint8_t* dst,
            int dstOffset,
            int dstStrideBytes)
   {
      static constexpr auto rowSize = MicroTileWidth * (16 / 8);
      src += srcOffset;
      dst += dstOffset;

      for (int y = 0; y < MicroTileHeight; ++y) {
         std::memcpy(dst, src, rowSize);
         src += srcStrideBytes;
         dst += dstStrideBytes;
      }
   }
};

struct MicroTiler32
{
   /*
      32 bits per element:
       0:   0,  1,  2,  3,    8,  9, 10, 11,
       8:   4,  5,  6,  7,   12, 13, 14, 15,

      16:  16, 17, 18, 19,   24, 25, 26, 27,
      24:  20, 21, 22, 23,   28, 29, 30, 31,

      32:  32, 33, 34, 35,   40, 41, 42, 43,
      40:  36, 37, 38, 39,   44, 45, 46, 47,

      48:  48, 49, 50, 51,   56, 57, 58, 59,
      56:  52, 53, 54, 55,   60, 61, 62, 63,
   */

   static inline void
      apply(uint8_t* src,
            int srcOffset,
            int srcStrideBytes,
            uint8_t* dst,
            int dstOffset,
            int dstStrideBytes)
   {
      static constexpr auto groupSize = 4 * (32 / 8);
      src += srcOffset;
      dst += dstOffset;

      for (int y = 0; y < MicroTileHeight; y += 2) {
         auto dstRow1 = reinterpret_cast<uint32_t*>(dst);
         auto dstRow2 = reinterpret_cast<uint32_t*>(dst + dstStrideBytes);

         auto srcRow1 = reinterpret_cast<uint32_t*>(src);
         auto srcRow2 = reinterpret_cast<uint32_t*>(src + srcStrideBytes);

         std::memcpy(dstRow1 + 0, srcRow1 + 0, groupSize);
         std::memcpy(dstRow1 + 4, srcRow2 + 0, groupSize);

         std::memcpy(dstRow2 + 0, srcRow1 + 4, groupSize);
         std::memcpy(dstRow2 + 4, srcRow2 + 4, groupSize);

         src += srcStrideBytes * 2;
         dst += dstStrideBytes * 2;
      }
   }
};

template<bool MacroTiling>
struct MicroTiler64
{
   /*
      64 bits per element:
       0:   0,  1,    4,  5,    8,  9,   12, 13,
       8:   2,  3,    6,  7,   10, 11,   14, 15,

      16:  16, 17,   20, 21,   24, 25,   28, 29,
      24:  18, 19,   22, 23,   26, 27,   30, 31,

      32:  32, 33,   36, 37,   40, 41,   44, 45,
      40:  34, 35,   38, 39,   42, 43,   46, 47,

      48:  48, 49,   52, 53,   56, 57,   60, 61,
      56:  50, 51,   54, 55,   58, 59,   62, 63,
   */

   static inline void
      apply(uint8_t* src,
            int srcOffset,
            int srcStrideBytes,
            uint8_t* dst,
            int dstOffset,
            int dstStrideBytes)
   {
      static constexpr auto groupBytes = 2 * (64 / 8);
      const auto nextGroupOffset =
         srcOffset + (0x100 << (NumBankBits + NumPipeBits));

      for (int y = 0; y < MicroTileHeight; y += 2) {
         if (MacroTiling && y == 4) {
            // At y == 4 we hit the next group (at element offset 256)
            srcOffset = nextGroupOffset;
         }

         auto dstRow1 = reinterpret_cast<uint64_t*>(dst + dstOffset);
         auto dstRow2 = reinterpret_cast<uint64_t*>(dst + dstOffset + dstStrideBytes);

         auto srcRow1 = reinterpret_cast<uint64_t*>(src + srcOffset);
         auto srcRow2 = reinterpret_cast<uint64_t*>(src + srcOffset + srcStrideBytes);

         std::memcpy(dstRow1 + 0, srcRow1 + 0, groupBytes);
         std::memcpy(dstRow2 + 0, srcRow1 + 2, groupBytes);

         std::memcpy(dstRow1 + 2, srcRow1 + 4, groupBytes);
         std::memcpy(dstRow2 + 2, srcRow1 + 6, groupBytes);

         std::memcpy(dstRow1 + 4, srcRow2 + 0, groupBytes);
         std::memcpy(dstRow2 + 4, srcRow2 + 2, groupBytes);

         std::memcpy(dstRow1 + 6, srcRow2 + 4, groupBytes);
         std::memcpy(dstRow2 + 6, srcRow2 + 6, groupBytes);

         srcOffset += 2 * srcStrideBytes;
         dstOffset += 2 * dstStrideBytes;
      }
   }
};

template<bool MacroTiling>
struct MicroTiler128
{
   /*
      128 bits per element:
         0:   0,  2,    4,  6,    8, 10,   12, 14,
         8:   1,  3,    5,  7,    9, 11,   13, 15,

        16:  16, 18,   20, 22,   24, 26,   28, 30,
        24:  17, 19,   21, 23,   25, 27,   29, 31,

        32:  32, 34,   36, 38,   40, 42,   44, 46,
        40:  33, 35,   37, 39,   41, 43,   45, 47,

        48:  48, 50,   52, 54,   56, 58,   60, 62,
        56:  49, 51,   53, 55,   57, 59,   61, 63,
   */

   static inline void
      apply(uint8_t* src,
            int srcOffset,
            int srcStrideBytes,
            uint8_t* dst,
            int dstOffset,
            int dstStrideBytes)
   {
      static constexpr auto elemBytes = 128 / 8;

      for (int y = 0; y < MicroTileHeight; y += 2) {
         auto dstRow1 = reinterpret_cast<uint8_t*>(dst + dstOffset);
         auto dstRow2 = reinterpret_cast<uint8_t*>(dst + dstOffset + dstStrideBytes);

         auto srcRow1 = reinterpret_cast<uint8_t*>(src + srcOffset);
         auto srcRow2 = reinterpret_cast<uint8_t*>(src + srcOffset + srcStrideBytes);

         std::memcpy(dstRow1 + 0 * elemBytes, srcRow1 + 0 * elemBytes, elemBytes);
         std::memcpy(dstRow1 + 1 * elemBytes, srcRow1 + 2 * elemBytes, elemBytes);
         std::memcpy(dstRow2 + 0 * elemBytes, srcRow1 + 1 * elemBytes, elemBytes);
         std::memcpy(dstRow2 + 1 * elemBytes, srcRow1 + 3 * elemBytes, elemBytes);

         std::memcpy(dstRow1 + 2 * elemBytes, srcRow1 + 4 * elemBytes, elemBytes);
         std::memcpy(dstRow1 + 3 * elemBytes, srcRow1 + 6 * elemBytes, elemBytes);
         std::memcpy(dstRow2 + 2 * elemBytes, srcRow1 + 5 * elemBytes, elemBytes);
         std::memcpy(dstRow2 + 3 * elemBytes, srcRow1 + 7 * elemBytes, elemBytes);

         std::memcpy(dstRow1 + 4 * elemBytes, srcRow2 + 0 * elemBytes, elemBytes);
         std::memcpy(dstRow1 + 5 * elemBytes, srcRow2 + 2 * elemBytes, elemBytes);
         std::memcpy(dstRow2 + 4 * elemBytes, srcRow2 + 1 * elemBytes, elemBytes);
         std::memcpy(dstRow2 + 5 * elemBytes, srcRow2 + 3 * elemBytes, elemBytes);

         std::memcpy(dstRow1 + 6 * elemBytes, srcRow2 + 4 * elemBytes, elemBytes);
         std::memcpy(dstRow1 + 7 * elemBytes, srcRow2 + 6 * elemBytes, elemBytes);
         std::memcpy(dstRow2 + 6 * elemBytes, srcRow2 + 5 * elemBytes, elemBytes);
         std::memcpy(dstRow2 + 7 * elemBytes, srcRow2 + 7 * elemBytes, elemBytes);

         if (MacroTiling) {
            srcOffset += 0x100 << (NumBankBits + NumPipeBits);
         } else {
            srcOffset += 2 * srcStrideBytes;
         }

         dstOffset += 2 * dstStrideBytes;
      }
   }
};

template<int BytesPerElement>
struct MicroTilerDepth
{
   /*
      depth elements:
          0:   0,  1,  4,  5,   16, 17, 20, 21,
          8:   2,  3,  6,  7,   18, 19, 22, 23,
         16:   8,  9, 12, 13,   24, 25, 28, 29,
         24:  10, 11, 14, 15,   26, 27, 30, 31,

         32:  32, 33, 36, 37,   48, 49, 52, 53,
         40:  34, 35, 38, 39,   50, 51, 54, 55,
         48:  40, 41, 44, 45,   56, 57, 60, 61,
         56:  42, 43, 46, 47,   58, 59, 62, 63,
   */

   static inline void
      apply(uint8_t* src,
            int srcOffset,
            int srcStrideBytes,
            uint8_t* dst,
            int dstOffset,
            int dstStrideBytes)
   {
      static constexpr auto elemBytes = BytesPerElement;
      static constexpr auto groupBytes = elemBytes * 2;

      for (int y = 0; y < MicroTileHeight; y += 4) {
         auto dstRow1 = dst + dstOffset;
         auto dstRow2 = dst + dstOffset + dstStrideBytes;
         auto dstRow3 = dst + dstOffset + dstStrideBytes * 2;
         auto dstRow4 = dst + dstOffset + dstStrideBytes * 3;

         for (int x = 0; x < MicroTileWidth; x += 4) {
            auto srcRow1 = src + srcOffset;
            auto srcRow2 = src + srcOffset + srcStrideBytes;

            std::memcpy(dstRow1 + 0 * elemBytes, srcRow1 + 0 * elemBytes, groupBytes);
            std::memcpy(dstRow1 + 2 * elemBytes, srcRow1 + 4 * elemBytes, groupBytes);
            std::memcpy(dstRow2 + 0 * elemBytes, srcRow1 + 2 * elemBytes, groupBytes);
            std::memcpy(dstRow2 + 2 * elemBytes, srcRow1 + 6 * elemBytes, groupBytes);

            std::memcpy(dstRow3 + 0 * elemBytes, srcRow2 + 0 * elemBytes, groupBytes);
            std::memcpy(dstRow3 + 2 * elemBytes, srcRow2 + 4 * elemBytes, groupBytes);
            std::memcpy(dstRow4 + 0 * elemBytes, srcRow2 + 2 * elemBytes, groupBytes);
            std::memcpy(dstRow4 + 2 * elemBytes, srcRow2 + 6 * elemBytes, groupBytes);

            srcOffset += srcStrideBytes * 2;
            dstRow1 += elemBytes * 4;
            dstRow2 += elemBytes * 4;
            dstRow3 += elemBytes * 4;
            dstRow4 += elemBytes * 4;
         }

         dstOffset += dstStrideBytes * 4;
      }
   }
};

template<typename MicroTiler>
static void
applyMicroTiler(const SurfaceDescription& desc,
                const SurfaceInfo& info,
                void* src,
                void* dst,
                int dstStrideBytes,
                int sliceOffset,
                int microTilesPerRow,
                int microTilesNumRows,
                int microTileBytes)
{
   const auto bytesPerElement = info.bpp / 8;
   auto microTileOffset = sliceOffset;

   for (auto microTileY = 0; microTileY < microTilesNumRows; ++microTileY) {
      for (auto microTileX = 0; microTileX < microTilesPerRow; ++microTileX) {
         const auto pixelX = microTileX * MicroTileWidth;
         const auto pixelY = microTileY * MicroTileHeight;
         const auto dstOffset =
            pixelX * bytesPerElement + pixelY * dstStrideBytes;

         MicroTiler::apply(static_cast<uint8_t*>(src),
                           microTileOffset,
                           MicroTileWidth* bytesPerElement,
                           static_cast<uint8_t*>(dst),
                           dstOffset,
                           dstStrideBytes);
         microTileOffset += microTileBytes;
      }
   }
}

static void
untileMicroSurface(const SurfaceDescription& desc,
                   const SurfaceInfo& info,
                   void* src,
                   void* dst,
                   int slice,
                   int sample)
{
   const auto bytesPerElement = info.bpp / 8;

   const auto microTileThickness = getMicroTileThickness(info.tileMode);
   const auto microTileBytes =
      MicroTileWidth * MicroTileHeight * microTileThickness
      * bytesPerElement * desc.numSamples;

   const auto microTilesPerRow = info.pitch / MicroTileWidth;
   const auto microTilesNumRows = info.height / MicroTileHeight;

   const auto microTileIndexZ = slice / microTileThickness;
   const  auto sliceBytes =
      info.pitch * info.height * microTileThickness * bytesPerElement;
   const auto sliceOffset = microTileIndexZ * sliceBytes;

   // Calculate offset within thick slices for current slice
   auto thickSliceOffset = 0;
   if (microTileThickness > 1 && slice > 0) {
      thickSliceOffset = (slice % microTileThickness) * (microTileBytes / microTileThickness);
   }

   const auto dstStrideBytes = info.pitch * bytesPerElement;

   const auto sampleOffset = sample * (microTileBytes / desc.numSamples);
   const auto sampleSliceOffset = sliceOffset + sampleOffset + thickSliceOffset;

   if (desc.use & SurfaceUse::DepthBuffer) {
      // TODO: Implement depth tiling for sample > 0
      decaf_check(sample == 0);

      switch (info.bpp) {
      case 16:
         applyMicroTiler<MicroTilerDepth<2>>(desc, info, src, dst, dstStrideBytes,
                                             sampleSliceOffset,
                                             microTilesPerRow, microTilesNumRows,
                                             microTileBytes);
         break;
      case 32:
         applyMicroTiler<MicroTilerDepth<4>>(desc, info, src, dst, dstStrideBytes,
                                             sampleSliceOffset,
                                             microTilesPerRow, microTilesNumRows,
                                             microTileBytes);
         break;
      case 64:
         applyMicroTiler<MicroTilerDepth<8>>(desc, info, src, dst, dstStrideBytes,
                                             sampleSliceOffset,
                                             microTilesPerRow, microTilesNumRows,
                                             microTileBytes);
         break;
      default:
         decaf_abort("Invalid depth bpp");
      }

      return;
   }

   switch (info.bpp) {
   case 8:
      applyMicroTiler<MicroTiler8>(desc, info, src, dst, dstStrideBytes,
                                   sampleSliceOffset,
                                   microTilesPerRow, microTilesNumRows,
                                   microTileBytes);
      break;
   case 16:
      applyMicroTiler<MicroTiler16>(desc, info, src, dst, dstStrideBytes,
                                    sampleSliceOffset,
                                    microTilesPerRow, microTilesNumRows,
                                    microTileBytes);
      break;
   case 32:
      applyMicroTiler<MicroTiler32>(desc, info, src, dst, dstStrideBytes,
                                    sampleSliceOffset,
                                    microTilesPerRow, microTilesNumRows,
                                    microTileBytes);
      break;
   case 64:
      applyMicroTiler<MicroTiler64<false>>(desc, info, src, dst, dstStrideBytes,
                                           sampleSliceOffset,
                                           microTilesPerRow, microTilesNumRows,
                                           microTileBytes);
      break;
   case 128:
      applyMicroTiler<MicroTiler128<false>>(desc, info, src, dst, dstStrideBytes,
                                            sampleSliceOffset,
                                            microTilesPerRow, microTilesNumRows,
                                            microTileBytes);
      break;
   default:
      decaf_abort("Invalid bpp");
   }
}

template<typename MicroTiler>
static void
applyMacroTiling(const SurfaceDescription& desc,
                 const SurfaceInfo& info,
                 void* src,
                 void* dst,
                 int dstStrideBytes,
                 int sampleOffset,
                 int sliceOffset,
                 int thickSliceOffset,
                 int bankSliceRotation,
                 int sampleSliceRotation,
                 int pipeSliceRotation,
                 int bankSwapWidth,
                 int macroTileWidth,
                 int macroTileHeight,
                 int macroTilesPerRow,
                 int macroTilesNumRows,
                 int macroTileBytes,
                 int microTileBytes)
{
   static const uint32_t bankSwapOrder[] = { 0, 1, 3, 2 };
   const auto bytesPerElement = info.bpp / 8;
   auto macroTileOffset = 0;
   auto macroTileIndex = 0;

   for (auto macroTileY = 0; macroTileY < macroTilesNumRows; ++macroTileY) {
      for (auto macroTileX = 0; macroTileX < macroTilesPerRow; ++macroTileX) {
         const auto totalOffset =
            ((sliceOffset + macroTileOffset) >> (NumBankBits + NumPipeBits))
            + sampleOffset + thickSliceOffset;
         const auto offsetHigh =
            (totalOffset & ~GroupMask) << (NumBankBits + NumPipeBits);
         const auto offsetLow = totalOffset & GroupMask;

         auto bankSwapRotation = 0;
         if (bankSwapWidth) {
            const auto swapIndex = ((macroTileX * macroTileWidth * MicroTileWidth) / bankSwapWidth);
            bankSwapRotation = bankSwapOrder[swapIndex % NumBanks];
         }

         for (auto microTileY = 0; microTileY < macroTileHeight; ++microTileY) {
            for (auto microTileX = 0; microTileX < macroTileWidth; ++microTileX) {
               const  auto pixelX =
                  (macroTileX * macroTileWidth + microTileX) * MicroTileWidth;
               const auto pixelY =
                  (macroTileY * macroTileHeight + microTileY) * MicroTileHeight;
               const auto dstOffset =
                  pixelX * bytesPerElement + pixelY * dstStrideBytes;

               // Calculate bank & pipe
               auto bank = ((pixelX >> 3) & 1) ^ ((pixelY >> 5) & 1);
               bank |= (((pixelX >> 4) & 1) ^ ((pixelY >> 4) & 1)) << 1;
               bank ^= (desc.bankSwizzle + bankSliceRotation) & (NumBanks - 1);
               bank ^= sampleSliceRotation;

               if (bankSwapWidth) {
                  bank ^= bankSwapRotation;
               }

               auto pipe = ((pixelX >> 3) & 1) ^ ((pixelY >> 3) & 1);
               pipe ^= (desc.pipeSwizzle + pipeSliceRotation) & (NumPipes - 1);

               auto microTileOffset =
                  (bank << (NumGroupBits + NumPipeBits))
                  + (pipe << NumGroupBits) + offsetHigh + offsetLow;

               MicroTiler::apply(static_cast<uint8_t*>(src),
                                 microTileOffset,
                                 MicroTileWidth* bytesPerElement,
                                 static_cast<uint8_t*>(dst),
                                 dstOffset,
                                 dstStrideBytes);
            }
         }

         macroTileOffset += macroTileBytes;
         macroTileIndex++;
      }
   }
}


static void
untileMacroSurface(const SurfaceDescription& desc,
                   const SurfaceInfo& info,
                   void* src,
                   void* dst,
                   int slice,
                   int sample)
{
   const auto bytesPerElement = info.bpp / 8;

   const auto microTileThickness = getMicroTileThickness(info.tileMode);
   const auto microTileBytes =
      MicroTileWidth * MicroTileHeight * microTileThickness
      * bytesPerElement * desc.numSamples;

   const auto macroTileWidth = getMacroTileWidth(info.tileMode);
   const auto macroTileHeight = getMacroTileHeight(info.tileMode);
   const auto macroTileBytes =
      macroTileWidth * macroTileHeight * microTileBytes;

   const auto macroTilesPerRow = info.pitch / (macroTileWidth * MicroTileWidth);
   const auto macroTilesNumRows = info.height / (macroTileHeight * MicroTileHeight);
   const auto dstStrideBytes = info.pitch * bytesPerElement;

   const auto macroTilesPerSlice = macroTilesPerRow * macroTilesNumRows;
   const auto sliceOffset =
      (slice / microTileThickness) * macroTilesPerSlice * macroTileBytes;

   // Calculate offset within thick slices for current slice
   auto thickSliceOffset = 0;
   if (microTileThickness > 1 && slice > 0) {
      thickSliceOffset = (slice % microTileThickness) * (microTileBytes / microTileThickness);
   }

   // Depth tiling is different for samples, not yet implemented
   decaf_check(!(desc.use & SurfaceUse::DepthBuffer) || sample == 0);
   const auto sampleOffset = sample * (microTileBytes / desc.numSamples);

   // Calculate bank / pipe rotation
   auto bankSliceRotation = 0;
   auto sampleSliceRotation = 0;
   auto pipeSliceRotation = 0;
   auto bankSwapWidth = 0;

   switch (info.tileMode) {
   case TileMode::Macro2DTiledThin1:
   case TileMode::Macro2DTiledThin2:
   case TileMode::Macro2DTiledThin4:
   case TileMode::Macro2DTiledThick:
   case TileMode::Macro2BTiledThin1:
   case TileMode::Macro2BTiledThin2:
   case TileMode::Macro2BTiledThin4:
   case TileMode::Macro2BTiledThick:
      bankSliceRotation = ((NumBanks >> 1) - 1)* (slice / microTileThickness);
      sampleSliceRotation = ((NumBanks >> 1) + 1)* sample;
      break;
   case TileMode::Macro3DTiledThin1:
   case TileMode::Macro3DTiledThick:
   case TileMode::Macro3BTiledThin1:
   case TileMode::Macro3BTiledThick:
      bankSliceRotation = (slice / microTileThickness) / NumPipes;
      pipeSliceRotation = (slice / microTileThickness);
      break;
   }

   switch (info.tileMode) {
   case TileMode::Macro2BTiledThin1:
   case TileMode::Macro2BTiledThin2:
   case TileMode::Macro2BTiledThin4:
   case TileMode::Macro2BTiledThick:
   case TileMode::Macro3BTiledThin1:
   case TileMode::Macro3BTiledThick:
      bankSwapWidth = computeSurfaceBankSwappedWidth(info.tileMode, info.bpp,
                                                     desc.numSamples,
                                                     info.pitch);
      break;
   }

   if (desc.use & SurfaceUse::DepthBuffer) {
      // TODO: Implement depth tiling for sample > 0
      decaf_check(sample == 0);

      switch (info.bpp) {
      case 16:
         applyMacroTiling<MicroTilerDepth<2>>(desc, info, src, dst, dstStrideBytes,
                                              sampleOffset, sliceOffset, thickSliceOffset,
                                              bankSliceRotation, sampleSliceRotation,
                                              pipeSliceRotation, bankSwapWidth,
                                              macroTileWidth, macroTileHeight,
                                              macroTilesPerRow, macroTilesNumRows,
                                              macroTileBytes, microTileBytes);
         break;
      case 32:
         applyMacroTiling<MicroTilerDepth<4>>(desc, info, src, dst, dstStrideBytes,
                                              sampleOffset, sliceOffset, thickSliceOffset,
                                              bankSliceRotation, sampleSliceRotation,
                                              pipeSliceRotation, bankSwapWidth,
                                              macroTileWidth, macroTileHeight,
                                              macroTilesPerRow, macroTilesNumRows,
                                              macroTileBytes, microTileBytes);
         break;
      case 64:
         applyMacroTiling<MicroTilerDepth<8>>(desc, info, src, dst, dstStrideBytes,
                                              sampleOffset, sliceOffset, thickSliceOffset,
                                              bankSliceRotation, sampleSliceRotation,
                                              pipeSliceRotation, bankSwapWidth,
                                              macroTileWidth, macroTileHeight,
                                              macroTilesPerRow, macroTilesNumRows,
                                              macroTileBytes, microTileBytes);
         break;
      default:
         decaf_abort("Invalid depth surface bpp");
      }

      return;
   }

   // Do the tiling
   switch (info.bpp) {
   case 8:
      applyMacroTiling<MicroTiler8>(desc, info, src, dst, dstStrideBytes,
                                    sampleOffset, sliceOffset, thickSliceOffset,
                                    bankSliceRotation, sampleSliceRotation,
                                    pipeSliceRotation, bankSwapWidth,
                                    macroTileWidth, macroTileHeight,
                                    macroTilesPerRow, macroTilesNumRows,
                                    macroTileBytes, microTileBytes);
      break;
   case 16:
      applyMacroTiling<MicroTiler16>(desc, info, src, dst, dstStrideBytes,
                                     sampleOffset, sliceOffset, thickSliceOffset,
                                     bankSliceRotation, sampleSliceRotation,
                                     pipeSliceRotation, bankSwapWidth,
                                     macroTileWidth, macroTileHeight,
                                     macroTilesPerRow, macroTilesNumRows,
                                     macroTileBytes, microTileBytes);
      break;
   case 32:
      applyMacroTiling<MicroTiler32>(desc, info, src, dst, dstStrideBytes,
                                     sampleOffset, sliceOffset, thickSliceOffset,
                                     bankSliceRotation, sampleSliceRotation,
                                     pipeSliceRotation, bankSwapWidth,
                                     macroTileWidth, macroTileHeight,
                                     macroTilesPerRow, macroTilesNumRows,
                                     macroTileBytes, microTileBytes);
      break;
   case 64:
      applyMacroTiling<MicroTiler64<true>>(desc, info, src, dst, dstStrideBytes,
                                           sampleOffset, sliceOffset, thickSliceOffset,
                                           bankSliceRotation, sampleSliceRotation,
                                           pipeSliceRotation, bankSwapWidth,
                                           macroTileWidth, macroTileHeight,
                                           macroTilesPerRow, macroTilesNumRows,
                                           macroTileBytes, microTileBytes);
      break;
   case 128:
      applyMacroTiling<MicroTiler128<true>>(desc, info, src, dst, dstStrideBytes,
                                            sampleOffset, sliceOffset, thickSliceOffset,
                                            bankSliceRotation, sampleSliceRotation,
                                            pipeSliceRotation, bankSwapWidth,
                                            macroTileWidth, macroTileHeight,
                                            macroTilesPerRow, macroTilesNumRows,
                                            macroTileBytes, microTileBytes);
      break;
   default:
      decaf_abort("Invalid surface bpp");
   }
}


/**
 * Untile all slices of an image (aka mip level = 0);
 *
 * @param src Points to image
 * @param dst Points to image slice
 */
void
untileImage(const SurfaceDescription& desc,
            void* src,
            void* dst)
{
   untileMip(desc, src, dst, 0);
}


/**
 * Untile a single slice of an image (aka mip level = 0).
 *
 * @param src Points to image
 * @param dst Points to image slice
 */
void
untileImageSlice(const SurfaceDescription& desc,
                 void* src,
                 void* dst,
                 int slice)
{
   untileMipSlice(desc, src, dst, 0, slice);
}


/**
 * Untile a single slice of a single mip level.
 *
 * @param src Points to mip
 * @param dst Points to mip slice
 */
void
untileMipSlice(const SurfaceDescription& desc,
               void* src,
               void* dst,
               int level,
               int slice)
{
   const auto info = computeSurfaceInfo(desc, level);

   // Multi-sample decoding is not supported yet.
   decaf_check(desc.numSamples == 1);
   auto sample = 0;

   switch (info.tileMode) {
   case TileMode::LinearGeneral:
   case TileMode::LinearAligned:
      // Already "untiled"
      return;
   case TileMode::Micro1DTiledThin1:
   case TileMode::Micro1DTiledThick:
      untileMicroSurface(desc, info, src, dst, slice, sample);
      break;
   case TileMode::Macro2DTiledThin1:
   case TileMode::Macro2DTiledThin2:
   case TileMode::Macro2DTiledThin4:
   case TileMode::Macro2DTiledThick:
   case TileMode::Macro2BTiledThin1:
   case TileMode::Macro2BTiledThin2:
   case TileMode::Macro2BTiledThin4:
   case TileMode::Macro2BTiledThick:
   case TileMode::Macro3DTiledThin1:
   case TileMode::Macro3DTiledThick:
   case TileMode::Macro3BTiledThin1:
   case TileMode::Macro3BTiledThick:
      untileMacroSurface(desc, info, src, dst, slice, sample);
      break;
   default:
      decaf_abort("Invalid tile mode");
   }
}


/**
 * Untile all slices within a single mip.
 *
 * @param src Points to mip
 * @param dst Points to mip
 */
void
untileMip(const SurfaceDescription& desc,
          void* src,
          void* dst,
          int level)
{
   const auto info = computeSurfaceInfo(desc, level);
   auto numSlices = std::min(desc.numSlices, info.depth);

   for (auto slice = 0u; slice < numSlices; ++slice) {
      untileMipSlice(desc,
                     src,
                     reinterpret_cast<uint8_t*>(dst) + info.sliceSize * slice,
                     level, slice);
   }
}


/**
 * Untile all slices at every mip level of a mipmap.
 *
 * @param src Points to mipmap
 * @param dst Points to mipmap
 */
void
untileMipMap(const SurfaceDescription& desc,
             void* src,
             void* dst)
{
   auto mipOffset = size_t { 0 };
   auto baseInfo = computeSurfaceInfo(desc, 0);

   for (auto level = 1u; level < desc.numLevels; ++level) {
      auto info = computeSurfaceInfo(desc, level);
      mipOffset = align_up(mipOffset, info.baseAlign);
      untileMip(desc,
                reinterpret_cast<uint8_t*>(src) + mipOffset,
                reinterpret_cast<uint8_t*>(dst) + mipOffset,
                level);
      mipOffset += info.surfSize;
   }
}


} // namespace gpu::tiling::cpu
