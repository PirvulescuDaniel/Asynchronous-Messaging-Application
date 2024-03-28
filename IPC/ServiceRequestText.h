#pragma once
#include "IService.h"
#include "pch.h"

/*
	Class responsible for handling a text-type request.
*/
class ServiceRequestText : public IService
{
public:

	using SocketPtr = std::shared_ptr<asio::ip::tcp::socket>;

	ServiceRequestText(SocketPtr aSocket);

	/*
		Start the handle process.
	*/
	void StartHandling() override;

private:

	/*
		It will be called after the request has been received.
	*/
	void OnRequestReceived();

	/*
		It process the request and generate and send a response.
	*/
	void ProcessRequest();

	/*
		It will be called after the response has been sent.
	*/
	void OnResponseSent(const asio::error_code& aErrorCode, std::size_t aBytesTransferred);

	SocketPtr mSocket;
};