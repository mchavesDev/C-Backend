//
// Created by mario on 10/1/26.
//

#ifndef C_BACKEND_CONTROLLER_H
#define C_BACKEND_CONTROLLER_H
#include "httpResponse.h"
#include "../headers/httpResponse.h"
#include "../headers/httpStatusCodes.h"

std::stringstream stringifyResponse(const httpResponse &response);
#endif //C_BACKEND_CONTROLLER_H