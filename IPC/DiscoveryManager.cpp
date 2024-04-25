#include "pch.h"
#include "DiscoveryManager.h"
#include "UDPBroadcastSender.h"

DiscoveryManager::DiscoveryManager(std::string_view aBroadcastIP, unsigned short aPort)
	:mBroadcastSender(new UDPBroadcastSender(mIoService, aBroadcastIP, aPort))
	,mTimer(nullptr)
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
	// Do not start another recurrent broadcasting if another is already in progress.
	if (!mBroadcastStoped)
		return;

	mBroadcastStoped = false;
	mTimer.reset(new asio::steady_timer(mIoService, aDelay));
	
	if(mTimer)
		mTimer->async_wait(std::bind(&DiscoveryManager::HandleTimeExpired, this, std::placeholders::_1, aDelay));
}

void DiscoveryManager::StopRecurrentBroadcasting()
{
	mBroadcastStoped = true;
}

void DiscoveryManager::HandleTimeExpired(const asio::error_code& aErrorCode, BroadcastDelay aDelay)
{
	// Stop the recurrent broadcasting process if errors have occurred.
	if (aErrorCode.value() != 0)
	{
		mBroadcastStoped = true;
		return;
	}

	if (mBroadcastStoped)
		return;

	mBroadcastSender->BroadcastAsync(mMessageHello);

	mTimer->expires_at(mTimer->expiry() + aDelay);
	mTimer->async_wait(std::bind(&DiscoveryManager::HandleTimeExpired, this, std::placeholders::_1, aDelay));
}