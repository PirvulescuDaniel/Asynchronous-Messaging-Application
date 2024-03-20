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

asio::const_buffers_1 RequestText::GetBufferToSend() const
{
	const auto messageTypeInt = static_cast<int>(GetType());

	const auto bufferToSend = std::to_string(messageTypeInt) + mMessage;

	return asio::buffer(bufferToSend);
}