#pragma once
#include "cafe/libraries/cafe_hle_library.h"

namespace cafe::lzma920
{

class Library : public hle::Library
{
public:
   Library() :
      hle::Library(hle::LibraryId::lzma920, "lzma920.rpl")
   {
   }

protected:
   virtual void registerSymbols() override;

private:
};

} // namespace cafe::lzma920
