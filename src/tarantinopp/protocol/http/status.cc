#include "tarantinopp/protocol/http/status.h"

namespace tarantinopp {
namespace http {
// 1xx Informational
const std::string Status::STATUS_100_Continue = "100 Continue";
const std::string Status::STATUS_101_SwitchingProtocols =
    "101 Switching Protocols";
const std::string Status::STATUS_102_Processing = "102 Processing";
const std::string Status::STATUS_103_EarlyHints = "103 Early Hints";

// 2xx Success
const std::string Status::STATUS_200_OK = "200 OK";
const std::string Status::STATUS_201_Created = "201 Created";
const std::string Status::STATUS_202_Accepted = "202 Accepted";
const std::string Status::STATUS_203_NonAuthoritativeInformation =
    "203 Non-Authoritative Information";
const std::string Status::STATUS_204_NoContent = "204 No Content";
const std::string Status::STATUS_205_ResetContent = "205 Reset Content";
const std::string Status::STATUS_206_PartialContent = "206 Partial Content";
const std::string Status::STATUS_207_MultiStatus = "207 Multi-Status";
const std::string Status::STATUS_208_AlreadyReported = "208 Already Reported";
const std::string Status::STATUS_226_IMUsed = "226 IM Used";

// 3xx Redirection
const std::string Status::STATUS_300_MultipleChoices = "300 Multiple Choices";
const std::string Status::STATUS_301_MovedPermanently = "301 Moved Permanently";
const std::string Status::STATUS_302_Found = "302 Found";
const std::string Status::STATUS_303_SeeOther = "303 See Other";
const std::string Status::STATUS_304_NotModified = "304 Not Modified";
const std::string Status::STATUS_305_UseProxy = "305 Use Proxy";
const std::string Status::STATUS_307_TemporaryRedirect =
    "307 Temporary Redirect";
const std::string Status::STATUS_308_PermanentRedirect =
    "308 Permanent Redirect";

// 4xx Client Error
const std::string Status::STATUS_400_BadRequest = "400 Bad Request";
const std::string Status::STATUS_401_Unauthorized = "401 Unauthorized";
const std::string Status::STATUS_402_PaymentRequired = "402 Payment Required";
const std::string Status::STATUS_403_Forbidden = "403 Forbidden";
const std::string Status::STATUS_404_NotFound = "404 Not Found";
const std::string Status::STATUS_405_MethodNotAllowed =
    "405 Method Not Allowed";
const std::string Status::STATUS_406_NotAcceptable = "406 Not Acceptable";
const std::string Status::STATUS_407_ProxyAuthenticationRequired =
    "407 Proxy Authentication Required";
const std::string Status::STATUS_408_RequestTimeout = "408 Request Timeout";
const std::string Status::STATUS_409_Conflict = "409 Conflict";
const std::string Status::STATUS_410_Gone = "410 Gone";
const std::string Status::STATUS_411_LengthRequired = "411 Length Required";
const std::string Status::STATUS_412_PreconditionFailed =
    "412 Precondition Failed";
const std::string Status::STATUS_413_PayloadTooLarge = "413 Payload Too Large";
const std::string Status::STATUS_414_URITooLong = "414 URI Too Long";
const std::string Status::STATUS_415_UnsupportedMediaType =
    "415 Unsupported Media Type";
const std::string Status::STATUS_416_RangeNotSatisfiable =
    "416 Range Not Satisfiable";
const std::string Status::STATUS_417_ExpectationFailed =
    "417 Expectation Failed";
const std::string Status::STATUS_418_ImATeapot = "418 I'm a teapot";
const std::string Status::STATUS_421_MisdirectedRequest =
    "421 Misdirected Request";
const std::string Status::STATUS_422_UnprocessableEntity =
    "422 Unprocessable Entity";
const std::string Status::STATUS_423_Locked = "423 Locked";
const std::string Status::STATUS_424_FailedDependency = "424 Failed Dependency";
const std::string Status::STATUS_425_TooEarly = "425 Too Early";
const std::string Status::STATUS_426_UpgradeRequired = "426 Upgrade Required";
const std::string Status::STATUS_428_PreconditionRequired =
    "428 Precondition Required";
const std::string Status::STATUS_429_TooManyRequests = "429 Too Many Requests";
const std::string Status::STATUS_431_RequestHeaderFieldsTooLarge =
    "431 Request Header Fields Too Large";
const std::string Status::STATUS_451_UnavailableForLegalReasons =
    "451 Unavailable For Legal Reasons";

// 5xx Server Error
const std::string Status::STATUS_500_InternalServerError =
    "500 Internal Server Error";
const std::string Status::STATUS_501_NotImplemented = "501 Not Implemented";
const std::string Status::STATUS_502_BadGateway = "502 Bad Gateway";
const std::string Status::STATUS_503_ServiceUnavailable =
    "503 Service Unavailable";
const std::string Status::STATUS_504_GatewayTimeout = "504 Gateway Timeout";
const std::string Status::STATUS_505_HTTPVersionNotSupported =
    "505 HTTP Version Not Supported";
const std::string Status::STATUS_506_VariantAlsoNegotiates =
    "506 Variant Also Negotiates";
const std::string Status::STATUS_507_InsufficientStorage =
    "507 Insufficient Storage";
const std::string Status::STATUS_508_LoopDetected = "508 Loop Detected";
const std::string Status::STATUS_510_NotExtended = "510 Not Extended";
const std::string Status::STATUS_511_NetworkAuthenticationRequired =
    "511 Network Authentication Required";
}  // namespace http
}  // namespace tarantinopp