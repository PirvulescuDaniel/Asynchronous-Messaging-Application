#pragma once
#include "IService.h"
#include "pch.h"

/*
	Class responsible for processing text-type request and sending the response.
*/
class ServiceRequestText : public IService
{
public:

	using SocketPtr = std::shared_ptr<asio::ip::tcp::socket>;

	ServiceRequestText(SocketPtr aSocket, std::string_view aRequest);

	/*
		Start the processing.
	*/
	void Process() override;

private:

	/*
		Process the request.
	*/
	void ProcessRequest();

	/*
		Process the response.
	*/
	void ProcessResponse();

	/*
		It will be called after the response has been sent.
	*/
	void OnResponseSent(const asio::error_code& aErrorCode, std::size_t aBytesTransferred);

	/*
		Clean-up.
	*/
	void OnFinish();

	SocketPtr   mSocket;
	std::string mRequest;
	std::string mResponse;
};