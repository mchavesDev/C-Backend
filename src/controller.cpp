//
// Created by mario on 10/1/26.
//

#include "../headers/controller.h"

#include <iosfwd>
#include <sstream>

std::stringstream stringifyResponse(const httpResponse& response) {
    std::stringstream responseString;
    //response head
    responseString << response.getVersion() << " "
    << response.getStatus() << " "
    << HttpStatus::reasonPhrase(response.getStatus()) << "\r\n";
    //remaining headers
    responseString << "Server: " << response.getServer() << "\r\n";
    responseString << "Content-Type: " << response.getContentType() << "\r\n";
    // responseString << "Content-Length: " << response.getHeader("Content-Length") << "\r\n";
    return responseString;
}
