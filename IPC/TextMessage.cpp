#include "pch.h"
#include "TextMessage.h"

TextMessage::TextMessage(std::string_view aMessage)
:mMessage(aMessage.data())
{
}

IMessage::MessageType TextMessage::GetType() const
{
	return IMessage::MessageType::MESSAGE_TEXT;
}

asio::const_buffers_1 TextMessage::GetBuffer() const
{
	return asio::buffer(mMessage);
}