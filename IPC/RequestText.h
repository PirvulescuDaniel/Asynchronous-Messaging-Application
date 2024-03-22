#pragma once
#include "IRequest.h"

class RequestText : public IRequest
{
public:
	RequestText(std::string_view aMessage, unsigned int aRequestId);

	RequestType GetType() const override;

	unsigned int GetId() const override;

	std::string GetRequest() const override;

private:
	std::string  mMessage;
	unsigned int mRequestId;
};