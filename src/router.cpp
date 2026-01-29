//
// Created by mario on 10/1/26.
//

#include "../headers/router.h"

#include "../headers/controller.h"
/**
 * Check if request exists in endpoints and if request needs auth, return http status code
 */
int parseRequest(const std::unique_ptr<httpRequest> &request) {
    const std::string resource = request->getResource();
    if (!endpoints.contains(resource) ) {
        //send to controller with response not found
        return HttpStatus::NotFound;
    }
    if (endpoints.at(resource) == 1) {
        //check for auth in headers
        //temp logic for authenticated requests
        //will replace with actual tokenized authorization service
        const std::string username = *request->Body.find("username");
        if (!request->Body.empty() && controller::checkIfAuth(*request)) {
            // const auto auth = request->Headers.at("authorization");
            // request->Body;
            //auth token is incorrect send to Forbidden httpStatusCode
            return HttpStatus::OK;
        }
        //send Unauthorized httpStatusCode
        return HttpStatus::Unauthorized;
    }
    if (endpoints.at(resource) == 0) {
        //not private endpoint, send Continue httpStatusCode
        if (resource=="/signup") {
            controller::insertNewNonExistantUser(controller::getUserValuesFromRequest(*request));
        }
        return HttpStatus::OK;
    }

    //if request matches an endpoint and is badly formed send Invalid httpStatusCode
    return HttpStatus::Invalid;
}