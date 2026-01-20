//
// Created by mario on 10/1/26.
//

#include "../headers/router.h"
#include <iostream>
#include <map>
#include <memory>

#include "../headers/httpStatusCodes.h"
#include "../headers/httpRequest.h"


int parseRequest(const std::unique_ptr<httpRequest> &request) {
    const std::string resource = request->getResource();
    if (endpoints.find(resource) == endpoints.end() ) {
        //send to controller with response not found
        return HttpStatus::NotFound;
    }
    if (endpoints.at(resource) == 1) {
        //check for auth in headers
        //temp logic for authenticated requests
        //will replace with actual tokenized authorization service
        if (request->Headers.contains("authorization")) {
            const auto auth = request->Headers.at("authorization");


            //auth token is incorrect send to Forbidden httpStatusCode
            return HttpStatus::Forbidden;
        }
        //send Unauthorized httpStatusCode
        return HttpStatus::Unauthorized;
    }
    if (endpoints.at(resource) == 0) {
        //not private endpoint, send Continue httpStatusCode
        return HttpStatus::OK;
    }

    //if request matches an endpoint and is badly formed send Invalid httpStatusCode
    return HttpStatus::Invalid;
}