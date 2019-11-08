#pragma once
#include "ios/nn/ios_nn_ipc_server.h"
#include "nn/act/nn_act_clientstandardservice.h"

namespace ios::fpd::internal
{

struct ActClientStandardService : ::nn::act::services::ClientStandardService
{
   static nn::Result
   commandHandler(uint32_t unk1,
                  nn::ipc::CommandId command,
                  nn::ipc::CommandHandlerArgs &args);
};

} // namespace ios::fpd::internal
