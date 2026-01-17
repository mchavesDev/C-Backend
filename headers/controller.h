//
// Created by mario on 10/1/26.
//

#ifndef C_BACKEND_CONTROLLER_H
#define C_BACKEND_CONTROLLER_H
#include <zlib.h>
#include "httpResponse.h"
#include <pqxx/pqxx>

#include "../headers/httpStatusCodes.h"
std::string compress_gzip(const std::string& str,int compressionlevel);
std::stringstream stringifyResponse(const httpResponse &response);

#endif //C_BACKEND_CONTROLLER_H