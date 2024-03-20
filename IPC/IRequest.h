#pragma once

class IRequest
{
public:

	enum struct RequestType
	{
		MESSAGE_TEXT
	};

	virtual ~IRequest() = default;

	virtual RequestType           GetType()         const = 0;
																						      
	virtual unsigned int          GetId()           const = 0;

	virtual asio::const_buffers_1 GetBufferToSend() const = 0;

};