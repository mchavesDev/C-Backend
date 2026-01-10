//
// Created by mario on 10/1/26.
//

#ifndef C_BACKEND_HTTPREQUEST_H
#define C_BACKEND_HTTPREQUEST_H
#include <map>
#include <string>
class httpRequest {
    public:
    std::string Request[3];
    std::string Host;
    std::map<std::string, std::string> Headers;
    httpRequest(const char* buffer, ssize_t totalBytes);
    void setRequest(const std::string& request);
    void setHost(const std::string &host);
    void setHeaders(const std::string& key, const std::string &value);
    std::string getHeader(const std::string &key);
    std::string getHost() const;
    std::string getMethod() const;
    std::string getResource() const;
    std::string getHttpVersion() const;
};


#endif //C_BACKEND_HTTPREQUEST_H