#include "pch.h"
#include "RequestText.h"

RequestText::RequestText(std::string_view aMessage, unsigned int aRequestId)
:mMessage(aMessage)
,mRequestId(aRequestId)
{
}

IRequest::RequestType RequestText::GetType() const
{
	return IRequest::RequestType::MESSAGE_TEXT;
}

unsigned int RequestText::GetId() const
{
	return mRequestId;
}

std::string RequestText::GetRequest() const
{
  return mMessage;
}