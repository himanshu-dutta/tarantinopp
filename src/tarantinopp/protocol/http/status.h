#pragma once

#include <string>

namespace tarantinopp {
namespace http {
class HttpStatus {
 public:
  // 1xx Informational
  static const std::string STATUS_100_Continue;
  static const std::string STATUS_101_SwitchingProtocols;
  static const std::string STATUS_102_Processing;
  static const std::string STATUS_103_EarlyHints;

  // 2xx Success
  static const std::string STATUS_200_OK;
  static const std::string STATUS_201_Created;
  static const std::string STATUS_202_Accepted;
  static const std::string STATUS_203_NonAuthoritativeInformation;
  static const std::string STATUS_204_NoContent;
  static const std::string STATUS_205_ResetContent;
  static const std::string STATUS_206_PartialContent;
  static const std::string STATUS_207_MultiStatus;
  static const std::string STATUS_208_AlreadyReported;
  static const std::string STATUS_226_IMUsed;

  // 3xx Redirection
  static const std::string STATUS_300_MultipleChoices;
  static const std::string STATUS_301_MovedPermanently;
  static const std::string STATUS_302_Found;
  static const std::string STATUS_303_SeeOther;
  static const std::string STATUS_304_NotModified;
  static const std::string STATUS_305_UseProxy;
  static const std::string STATUS_307_TemporaryRedirect;
  static const std::string STATUS_308_PermanentRedirect;

  // 4xx Client Error
  static const std::string STATUS_400_BadRequest;
  static const std::string STATUS_401_Unauthorized;
  static const std::string STATUS_402_PaymentRequired;
  static const std::string STATUS_403_Forbidden;
  static const std::string STATUS_404_NotFound;
  static const std::string STATUS_405_MethodNotAllowed;
  static const std::string STATUS_406_NotAcceptable;
  static const std::string STATUS_407_ProxyAuthenticationRequired;
  static const std::string STATUS_408_RequestTimeout;
  static const std::string STATUS_409_Conflict;
  static const std::string STATUS_410_Gone;
  static const std::string STATUS_411_LengthRequired;
  static const std::string STATUS_412_PreconditionFailed;
  static const std::string STATUS_413_PayloadTooLarge;
  static const std::string STATUS_414_URITooLong;
  static const std::string STATUS_415_UnsupportedMediaType;
  static const std::string STATUS_416_RangeNotSatisfiable;
  static const std::string STATUS_417_ExpectationFailed;
  static const std::string STATUS_418_ImATeapot;
  static const std::string STATUS_421_MisdirectedRequest;
  static const std::string STATUS_422_UnprocessableEntity;
  static const std::string STATUS_423_Locked;
  static const std::string STATUS_424_FailedDependency;
  static const std::string STATUS_425_TooEarly;
  static const std::string STATUS_426_UpgradeRequired;
  static const std::string STATUS_428_PreconditionRequired;
  static const std::string STATUS_429_TooManyRequests;
  static const std::string STATUS_431_RequestHeaderFieldsTooLarge;
  static const std::string STATUS_451_UnavailableForLegalReasons;

  // 5xx Server Error
  static const std::string STATUS_500_InternalServerError;
  static const std::string STATUS_501_NotImplemented;
  static const std::string STATUS_502_BadGateway;
  static const std::string STATUS_503_ServiceUnavailable;
  static const std::string STATUS_504_GatewayTimeout;
  static const std::string STATUS_505_HTTPVersionNotSupported;
  static const std::string STATUS_506_VariantAlsoNegotiates;
  static const std::string STATUS_507_InsufficientStorage;
  static const std::string STATUS_508_LoopDetected;
  static const std::string STATUS_510_NotExtended;
  static const std::string STATUS_511_NetworkAuthenticationRequired;
};
}  // namespace http
}  // namespace tarantinopp