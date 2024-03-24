#pragma once
#include "IRequestHandler.h"

class RequestTextHandler : public IRequestHandler
{
public:
	void Handle(RequestPtr aRequest, std::string_view aServerResponse, asio::error_code& aErrorCode);
};