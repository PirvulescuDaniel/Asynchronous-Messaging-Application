#include "pch.h"
#include "RequestEncoder.h"
#include "IRequest.h"

std::string RequestEncoder::EncodeRequest(IRequest* aRequest)
{
  const auto& requestType = aRequest->GetType();

  std::string encodedRequest;

  switch (requestType)
  {
  case IRequest::RequestType::MESSAGE_TEXT:
    encodedRequest = EncodeTextRequest(aRequest);
  }

  return encodedRequest;
}

std::string RequestEncoder::EncodeTextRequest(IRequest* aRequest)
{
  const auto textTypeInt = static_cast<unsigned int>(IRequest::RequestType::MESSAGE_TEXT);

  const auto& rawMessage = aRequest->GetRequest();

  const char delim = '\n';

  const auto buffer = std::to_string(textTypeInt) + rawMessage + delim;

  return buffer;
}