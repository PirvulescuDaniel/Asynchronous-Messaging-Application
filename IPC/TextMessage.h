#pragma once

#include "IMessage.h"

class TextMessage : public IMessage
{
public:

	TextMessage(std::string_view aMessage);

	MessageType GetType() const override;

	asio::const_buffers_1 GetBuffer() const override;

private:
	std::string mMessage;
};