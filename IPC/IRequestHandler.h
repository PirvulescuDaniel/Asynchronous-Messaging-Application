#pragma once
#include "pch.h"

class IRequest;

/*
	Responsible for handling the sent requests.
*/
class IRequestHandler
{
public:
	using RequestPtr = std::shared_ptr<IRequest>;

	virtual void Handle(RequestPtr aRequest, std::string_view aServerResponse, asio::error_code& aErrorCode) = 0;
};