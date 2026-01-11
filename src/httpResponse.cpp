//
// Created by mario on 11/1/26.
//

#include "../headers/httpResponse.h"
#include "../headers/httpStatusCodes.h"

#include <sstream>
const std::string serverName = "C-backend";



httpResponse::httpResponse(const int statusCode,const httpRequest& request) {
    this->setStatus(statusCode);
    this->setVersion(request.getHttpVersion());
    this->setServer(serverName);
    this->setContentType("application/json");
    this->setBody(request.getResource(),statusCode);
    if (this->getVersion() == "HTTP/1.0") {
        this->setHeader("Content-Length", std::to_string(sizeof(this->getBody())));
    }

}

int httpResponse::getStatus() const {
    return this->Status;
}

std::string httpResponse::getVersion() const {
    return this->Version;
}

std::string httpResponse::getContentType() const {
    return this->ContentType;
}

std::string httpResponse::getBody() const {
    return this->Body;
}
std::string httpResponse::getServer() const{
    return this->Server ;
}
std::string httpResponse::getHeader(const std::string& key) const{
    return this->Headers.at(key) ;
}
void httpResponse::setStatus(const int status) {
    this->Status = status;
}

void httpResponse::setHeader(const std::string &key, const std::string &value) {
    this->Headers[key] = value;
}

void httpResponse::setVersion(const std::string &version) {
    this->Version = version;
}

void httpResponse::setContentType(const std::string &content_type) {
    this->ContentType = content_type;
}

void httpResponse::setBody(std::string resource, const int statusCode) {
    if (HttpStatus::isSuccessful(statusCode)) {

    }else if (HttpStatus::isClientError(statusCode)) {
        this->Body = HttpStatus::reasonPhrase(statusCode);
    }


    // this->Body = ;
}
void httpResponse::setServer(const std::string &server) {
    this->Server = server;
}
