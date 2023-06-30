#pragma once

#include <string>

namespace tarantinopp {
namespace http {
class HttpHeader {
 public:
  static const std::string Accept;
  static const std::string AcceptCharset;
  static const std::string AcceptEncoding;
  static const std::string AcceptLanguage;
  static const std::string AcceptRanges;
  static const std::string Age;
  static const std::string Allow;
  static const std::string Authorization;
  static const std::string CacheControl;
  static const std::string Connection;
  static const std::string ContentEncoding;
  static const std::string ContentLanguage;
  static const std::string ContentLength;
  static const std::string ContentLocation;
  static const std::string ContentMD5;
  static const std::string ContentRange;
  static const std::string ContentType;
  static const std::string Cookie;
  static const std::string Date;
  static const std::string ETag;
  static const std::string Expect;
  static const std::string Expires;
  static const std::string From;
  static const std::string Host;
  static const std::string IfMatch;
  static const std::string IfModifiedSince;
  static const std::string IfNoneMatch;
  static const std::string IfRange;
  static const std::string IfUnmodifiedSince;
  static const std::string LastModified;
  static const std::string Location;
  static const std::string MaxForwards;
  static const std::string Pragma;
  static const std::string ProxyAuthenticate;
  static const std::string ProxyAuthorization;
  static const std::string Range;
  static const std::string Referer;
  static const std::string RetryAfter;
  static const std::string Server;
  static const std::string SetCookie;
  static const std::string TE;
  static const std::string Trailer;
  static const std::string TransferEncoding;
  static const std::string Upgrade;
  static const std::string UserAgent;
  static const std::string Vary;
  static const std::string Via;
  static const std::string Warning;
  static const std::string WWWAuthenticate;
};

}  // namespace http
}  // namespace tarantinopp
