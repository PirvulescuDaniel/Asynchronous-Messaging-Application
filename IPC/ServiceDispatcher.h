#pragma once
#include "pch.h"

class IService;

/*
	Class responsible for receiving the request, analyzing it and sending it to the appropriate service.
*/
class ServiceDispatcher : public std::enable_shared_from_this<ServiceDispatcher>
{
public:

	using SocketPtr     = std::shared_ptr<asio::ip::tcp::socket>;
	using RequestBuffer = asio::streambuf;
	using UICallback    = std::function<void(const wchar_t *, const wchar_t *, bool)>;

	ServiceDispatcher(SocketPtr aSocket);

	/*
		Read the request and start the dispatching process.
	*/
	void StartDispatching(UICallback aCallback);

private:

	/*
		It will be called after the request has been received.
	*/
	void OnRequestReceived(const asio::error_code& aErrorCode, std::size_t aBytesTransferred, UICallback aCallback);

	SocketPtr     mSocket;
	RequestBuffer mRequestBuffer;
};