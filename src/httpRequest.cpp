#include "../headers/httpRequest.h"
#include <iostream>
#include <sstream>
httpRequest::httpRequest(const char* buffer, const ssize_t totalBytes){
    int i = 0;
    int z = 0;
    int phase = 0;

    // int fullRequestIndex = 0;
    std::stringstream splicedRequest;

    while (z < totalBytes - 2){
        i=z;
        while (buffer[i] !='\r'){
            splicedRequest << buffer[i];
            i++;
        }
        if (z==0){
            this->setRequest(splicedRequest.str());
            phase = 1;
        }
        else if(phase == 1 && z > 0){
            this->setHost(splicedRequest.str().substr(6,sizeof(splicedRequest)));
            phase = 0;
        }
        else{
            const size_t del = splicedRequest.str().find(':');
            std::string key = splicedRequest.str().substr(0, del);
            std::string content = splicedRequest.str().substr(del + 2, sizeof(splicedRequest));
            this->setHeaders(key, content);
        }
        splicedRequest.str(std::string());
        z=i+2;
    }
}
void httpRequest::setRequest(const std::string& request){
    std::stringstream splitRequest(request);
    std::string temp;
    constexpr char del = ' ';
    int i = 0;
    while (getline(splitRequest, temp, del))
    {
        this->Request[i] = temp;
        i++;
    }
}
void httpRequest::setHost(const std::string &host){
    this->Host = host;
}
void httpRequest::setHeaders(const std::string& key, const std::string &value){
    this->Headers[key] = value;
}
std::string httpRequest::getHeader(const std::string &key) {
    return this->Headers[key];
}
std::string httpRequest::getHost() const {
    return this->Host;
}
std::string httpRequest::getMethod() const {
    return this->Request[0];
}
std::string httpRequest::getResource() const {
    return this->Request[1];
}
std::string httpRequest::getHttpVersion() const {
    return this->Request[2];
}