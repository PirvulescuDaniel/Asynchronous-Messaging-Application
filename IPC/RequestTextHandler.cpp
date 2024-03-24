#include "pch.h"
#include "RequestTextHandler.h"

void RequestTextHandler::Handle(RequestPtr aRequest, std::string_view aServerResponse, asio::error_code& aErrorCode)
{
	if (aErrorCode.value() == asio::error::operation_aborted)
	{
		// handle canceled request.
		return;
	}

	if (aErrorCode.value() != 0)
	{
		// handle failed request.
		return;
	}

	//handle success request.
}