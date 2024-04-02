#pragma once
#include "IRequest.h"

class IRequestHandler;

class HandlerFactory
{
public:

  using RequestHandlerPtr = std::unique_ptr<IRequestHandler>;

  HandlerFactory() = default;

  RequestHandlerPtr Create(IRequest::RequestType aRequestType);
};