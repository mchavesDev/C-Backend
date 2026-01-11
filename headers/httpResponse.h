//
// Created by mario on 11/1/26.
//

#ifndef C_BACKEND_HTTPRESPONSE_H
#define C_BACKEND_HTTPRESPONSE_H
#include <map>
#include <string>

#include "httpRequest.h"


class httpResponse {
public:
    int Status = 0;
    std::string Version;
    std::string Server;
    std::string ContentType;
    std::string Body;
    std::map<std::string, std::string> Headers;
    httpResponse(int statusCode,const httpRequest& request);
    int getStatus() const;
    std::string getVersion() const;
    std::string getContentType() const;
    std::string getBody() const;
    std::string getServer() const;
    std::string getHeader(const std::string& key) const;
    void setStatus(int status);
    void setVersion(const std::string &version);
    void setContentType(const std::string &content_type);
    void setBody(std::string resource,int statusCode);
    void setServer(const std::string &server);
    void setHeader(const std::string &key, const std::string &value);
};


#endif //C_BACKEND_HTTPRESPONSE_H