#include "tarantinopp/protocol/http/status.h"

namespace tarantinopp {
namespace http {
// 1xx Informational
const std::string HttpStatus::STATUS_100_Continue = "100 Continue";
const std::string HttpStatus::STATUS_101_SwitchingProtocols =
    "101 Switching Protocols";
const std::string HttpStatus::STATUS_102_Processing = "102 Processing";
const std::string HttpStatus::STATUS_103_EarlyHints = "103 Early Hints";

// 2xx Success
const std::string HttpStatus::STATUS_200_OK = "200 OK";
const std::string HttpStatus::STATUS_201_Created = "201 Created";
const std::string HttpStatus::STATUS_202_Accepted = "202 Accepted";
const std::string HttpStatus::STATUS_203_NonAuthoritativeInformation =
    "203 Non-Authoritative Information";
const std::string HttpStatus::STATUS_204_NoContent = "204 No Content";
const std::string HttpStatus::STATUS_205_ResetContent = "205 Reset Content";
const std::string HttpStatus::STATUS_206_PartialContent = "206 Partial Content";
const std::string HttpStatus::STATUS_207_MultiStatus = "207 Multi-Status";
const std::string HttpStatus::STATUS_208_AlreadyReported =
    "208 Already Reported";
const std::string HttpStatus::STATUS_226_IMUsed = "226 IM Used";

// 3xx Redirection
const std::string HttpStatus::STATUS_300_MultipleChoices =
    "300 Multiple Choices";
const std::string HttpStatus::STATUS_301_MovedPermanently =
    "301 Moved Permanently";
const std::string HttpStatus::STATUS_302_Found = "302 Found";
const std::string HttpStatus::STATUS_303_SeeOther = "303 See Other";
const std::string HttpStatus::STATUS_304_NotModified = "304 Not Modified";
const std::string HttpStatus::STATUS_305_UseProxy = "305 Use Proxy";
const std::string HttpStatus::STATUS_307_TemporaryRedirect =
    "307 Temporary Redirect";
const std::string HttpStatus::STATUS_308_PermanentRedirect =
    "308 Permanent Redirect";

// 4xx Client Error
const std::string HttpStatus::STATUS_400_BadRequest = "400 Bad Request";
const std::string HttpStatus::STATUS_401_Unauthorized = "401 Unauthorized";
const std::string HttpStatus::STATUS_402_PaymentRequired =
    "402 Payment Required";
const std::string HttpStatus::STATUS_403_Forbidden = "403 Forbidden";
const std::string HttpStatus::STATUS_404_NotFound = "404 Not Found";
const std::string HttpStatus::STATUS_405_MethodNotAllowed =
    "405 Method Not Allowed";
const std::string HttpStatus::STATUS_406_NotAcceptable = "406 Not Acceptable";
const std::string HttpStatus::STATUS_407_ProxyAuthenticationRequired =
    "407 Proxy Authentication Required";
const std::string HttpStatus::STATUS_408_RequestTimeout = "408 Request Timeout";
const std::string HttpStatus::STATUS_409_Conflict = "409 Conflict";
const std::string HttpStatus::STATUS_410_Gone = "410 Gone";
const std::string HttpStatus::STATUS_411_LengthRequired = "411 Length Required";
const std::string HttpStatus::STATUS_412_PreconditionFailed =
    "412 Precondition Failed";
const std::string HttpStatus::STATUS_413_PayloadTooLarge =
    "413 Payload Too Large";
const std::string HttpStatus::STATUS_414_URITooLong = "414 URI Too Long";
const std::string HttpStatus::STATUS_415_UnsupportedMediaType =
    "415 Unsupported Media Type";
const std::string HttpStatus::STATUS_416_RangeNotSatisfiable =
    "416 Range Not Satisfiable";
const std::string HttpStatus::STATUS_417_ExpectationFailed =
    "417 Expectation Failed";
const std::string HttpStatus::STATUS_418_ImATeapot = "418 I'm a teapot";
const std::string HttpStatus::STATUS_421_MisdirectedRequest =
    "421 Misdirected Request";
const std::string HttpStatus::STATUS_422_UnprocessableEntity =
    "422 Unprocessable Entity";
const std::string HttpStatus::STATUS_423_Locked = "423 Locked";
const std::string HttpStatus::STATUS_424_FailedDependency =
    "424 Failed Dependency";
const std::string HttpStatus::STATUS_425_TooEarly = "425 Too Early";
const std::string HttpStatus::STATUS_426_UpgradeRequired =
    "426 Upgrade Required";
const std::string HttpStatus::STATUS_428_PreconditionRequired =
    "428 Precondition Required";
const std::string HttpStatus::STATUS_429_TooManyRequests =
    "429 Too Many Requests";
const std::string HttpStatus::STATUS_431_RequestHeaderFieldsTooLarge =
    "431 Request Header Fields Too Large";
const std::string HttpStatus::STATUS_451_UnavailableForLegalReasons =
    "451 Unavailable For Legal Reasons";

// 5xx Server Error
const std::string HttpStatus::STATUS_500_InternalServerError =
    "500 Internal Server Error";
const std::string HttpStatus::STATUS_501_NotImplemented = "501 Not Implemented";
const std::string HttpStatus::STATUS_502_BadGateway = "502 Bad Gateway";
const std::string HttpStatus::STATUS_503_ServiceUnavailable =
    "503 Service Unavailable";
const std::string HttpStatus::STATUS_504_GatewayTimeout = "504 Gateway Timeout";
const std::string HttpStatus::STATUS_505_HTTPVersionNotSupported =
    "505 HTTP Version Not Supported";
const std::string HttpStatus::STATUS_506_VariantAlsoNegotiates =
    "506 Variant Also Negotiates";
const std::string HttpStatus::STATUS_507_InsufficientStorage =
    "507 Insufficient Storage";
const std::string HttpStatus::STATUS_508_LoopDetected = "508 Loop Detected";
const std::string HttpStatus::STATUS_510_NotExtended = "510 Not Extended";
const std::string HttpStatus::STATUS_511_NetworkAuthenticationRequired =
    "511 Network Authentication Required";
}  // namespace http
}  // namespace tarantinopp