#include "pch.h"
#include "UDPBroadcastSender.h"

UDPBroadcastSender::UDPBroadcastSender(asio::io_service& aService, std::string_view aIp, unsigned short aPort)
	:mService(aService)
	,mSocket(mService)
	,mBroadcastEndpoint(asio::ip::address::from_string(aIp.data()),aPort)
{
	mSocket.open(asio::ip::udp::v4());

	mSocket.set_option(asio::socket_base::reuse_address(true));
	mSocket.set_option(asio::socket_base::broadcast(true));
}

void UDPBroadcastSender::BroadcastAsync(const std::string& aMessage)
{
	mSocket.async_send_to(asio::buffer(aMessage), mBroadcastEndpoint,
		[](const asio::error_code& aErrorCode, std::size_t aBytesTransferred)
		{
			// We don't care if the message was sent or not.
		}
	);
}

void UDPBroadcastSender::StartBroadcasting(const std::string& aMessage, BroadcastDelay aDelay)
{
	// Do not start another broadcasting process if another is already in progress.
	if (!mStopped)
		return;

	mStopped = false;
	mTimer.reset(new asio::steady_timer(mService, aDelay));

	if (mTimer)
		mTimer->async_wait(std::bind(&UDPBroadcastSender::HandleTimeExpired, this, std::placeholders::_1, aDelay, aMessage));
}

void UDPBroadcastSender::StopBroadcasting()
{
	mStopped = true;
}

void UDPBroadcastSender::BroadcastSync(const std::string& aMessage)
{
	mSocket.send_to(asio::buffer(aMessage), mBroadcastEndpoint);
}

void UDPBroadcastSender::HandleTimeExpired(const asio::error_code& aErrorCode, BroadcastDelay aDelay, const std::string& aMessage)
{
	// Stop the recurrent broadcasting process if errors have occurred.
	if (aErrorCode.value() != 0)
	{
		mStopped = true;
		return;
	}

	if (mStopped)
		return;

	BroadcastAsync(aMessage);

	mTimer->expires_at(mTimer->expiry() + aDelay);
	mTimer->async_wait(std::bind(&UDPBroadcastSender::HandleTimeExpired, this, std::placeholders::_1, aDelay, aMessage));
}