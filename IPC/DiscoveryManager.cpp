#include "pch.h"
#include "DiscoveryManager.h"
#include "UDPBroadcastSender.h"

DiscoveryManager::DiscoveryManager(std::string_view aBroadcastIP, unsigned short aPort)
	:mBroadcaster(new UDPBroadcastSender(mIoService, aBroadcastIP, aPort))
{
	mWorker.reset(new asio::io_service::work(mIoService));
}

void DiscoveryManager::Broadcast()
{
	mBroadcaster->BroadcastAsync(mMessageHello);
}

void DiscoveryManager::StartRecurrentBroadcasting()
{
	// TODO
}

void DiscoveryManager::StopRecurrentBroadcasting()
{
	// TODO
}