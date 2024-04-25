#include "pch.h"
#include "DiscoveryManager.h"
#include "UDPBroadcastSender.h"
#include "UDPBroadcastListener.h"

DiscoveryManager::DiscoveryManager(std::string_view aBroadcastIP, unsigned short aPort)
	:mBroadcastSender(new UDPBroadcastSender(mIoService, aBroadcastIP, aPort))
	,mBroadcastListener(new UDPBroadcastListener(mIoService,aPort))
{
	mWorker.reset(new asio::io_service::work(mIoService));

	mThreadWorker.reset(new std::thread(
		[this]()
		{
			mIoService.run();
		}
	));
}

DiscoveryManager::~DiscoveryManager()
{
	mBroadcastSender->BroadcastSync(mMessageBye);

	mWorker.reset(nullptr);

	if (mThreadWorker && mThreadWorker->joinable())
		mThreadWorker->join();
}

void DiscoveryManager::Broadcast(const std::string& aMessage)
{
	mBroadcastSender->BroadcastAsync(aMessage);
}

void DiscoveryManager::StartRecurrentBroadcasting(BroadcastDelay aDelay)
{
	mBroadcastSender->StartBroadcasting(mMessageHello, aDelay);
}

void DiscoveryManager::StopRecurrentBroadcasting()
{
	mBroadcastSender->StopBroadcasting();
}

void DiscoveryManager::StartListening()
{
	mBroadcastListener->StartListening();
}

void DiscoveryManager::StopListening()
{
	mBroadcastListener->StopListening();
}