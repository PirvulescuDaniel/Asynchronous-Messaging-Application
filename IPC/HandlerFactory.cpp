#include "pch.h"
#include "HandlerFactory.h"
#include "RequestTextHandler.h"

HandlerFactory::RequestHandlerPtr HandlerFactory::Create(IRequest::RequestType aRequestType)
{
  switch (aRequestType)
  {
    case IRequest::RequestType::MESSAGE_TEXT:
      return std::make_unique<RequestTextHandler>();
  }

  return nullptr;
}