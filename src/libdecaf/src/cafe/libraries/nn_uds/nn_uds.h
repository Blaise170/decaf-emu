#pragma once
#include "cafe/libraries/cafe_hle_library.h"

namespace cafe::nn_uds
{

class Library : public hle::Library
{
public:
   Library() :
      hle::Library(hle::LibraryId::nn_uds, "nn_uds.rpl")
   {
   }

protected:
   virtual void registerSymbols() override;

private:
   void registerApiSymbols();
};

} // namespace cafe::nn_uds
