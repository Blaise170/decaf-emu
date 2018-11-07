#include "ios_acp_nn_miscservice.h"

#include "ios/nn/ios_nn_ipc_server_command.h"
#include "nn/acp/nn_acp_result.h"

#include <chrono>
#include <ctime>

using namespace nn::acp;
using namespace nn::ipc;

namespace ios::acp::internal
{

static nn::Result
getNetworkTime(CommandHandlerArgs &args)
{
   auto command = ServerCommand<MiscService::GetNetworkTime> { args };
   auto networkTime = std::chrono::microseconds(time(NULL)).count();
   auto unkValue = 1;
   command.WriteResponse(networkTime, unkValue);
   return ResultSuccess;
}

static nn::Result
getTitleMetaXml(CommandHandlerArgs &args)
{
   auto command = ServerCommand<MiscService::GetTitleMetaXml> { args };
   auto buffer = OutBuffer<ACPMetaXml> { };
   auto titleId = uint64_t { 0 };
   command.ReadRequest(buffer, titleId);

   // TODO: Update buffer with meta xml
   return ResultSuccess;
}

nn::Result
MiscService::commandHandler(uint32_t unk1,
                            CommandId command,
                            CommandHandlerArgs &args)
{
   switch (command) {
   case GetNetworkTime::command:
      return getNetworkTime(args);
   case GetTitleMetaXml::command:
      return getTitleMetaXml(args);
   default:
      return ResultSuccess;
   }
}

} // namespace ios::acp::internal
