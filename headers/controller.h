//
// Created by mario on 10/1/26.
//

#ifndef C_BACKEND_CONTROLLER_H
#define C_BACKEND_CONTROLLER_H
#include <zlib.h>
#include "httpResponse.h"
#include "user.h"
#include "httpStatusCodes.h"
#include "modelPqxx.h"
std::string compress_gzip(const std::string& str,int compressionLevel);
std::stringstream stringifyResponse(const httpResponse &response);
bool checkForCredentials(const std::string &username, const std::string &password);
bool checkIfAuth(httpRequest &request);
bool getUserByUsername(const std::string &username);
bool insertNewNonExistantUser(const std::string &username,const std::string &password);
bool getUserValuesFromRequest(httpRequest &request);

#endif //C_BACKEND_CONTROLLER_H
