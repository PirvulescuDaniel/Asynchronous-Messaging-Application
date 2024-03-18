#pragma once

class IMessage
{
public:

	enum struct MessageType
	{
		MESSAGE_TEXT
	};

	virtual ~IMessage() = default;

	virtual MessageType           GetType()   const = 0;

	virtual asio::const_buffers_1 GetBuffer() const = 0;

};