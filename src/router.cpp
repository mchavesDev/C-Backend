//
// Created by mario on 10/1/26.
//

#include "../headers/router.h"
#include <iostream>
#include <map>
#include <memory>

#include "../headers/httpStatusCodes.h"
#include "../headers/httpRequest.h"


void parseRequest(const std::unique_ptr<httpRequest> &request) {
    const std::string resource = request->getResource();
    if (endpoints.find(resource) == endpoints.end() ) {
        //send to controller with response not found
        std::cerr << HttpStatus::NotFound;
    }else {
        if (endpoints.at(resource) == 1) {
            bool authenticated = false;
            //check for auth in headers
            //temp logic for authenticated requests
            if (request->Headers.find("authorization") != request->Headers.end()) {
                authenticated = true;
            }
            if (!authenticated) {
                //send to controller with response Unauthorized
                std::cerr << HttpStatus::Unauthorized;

            }else {
                //send to controller and apply logic
                std::cout << HttpStatus::OK;
            }
        } else {

        }

    }
}