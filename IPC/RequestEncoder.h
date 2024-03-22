#pragma once

class IRequest;

/*
  Class responsible for the encode of a RAW formatted request into a buffer ready to be sent.
*/
class RequestEncoder
{
public:
  RequestEncoder() = default;

  std::string EncodeRequest(IRequest* aRequest);

private:
  std::string EncodeTextRequest(IRequest* aRequest);
};