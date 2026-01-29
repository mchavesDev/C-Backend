//
// Created by mario on 10/1/26.
//

#ifndef C_BACKEND_CONTROLLER_H
#define C_BACKEND_CONTROLLER_H
#include <dotenv.h>
#include <zlib.h>
#include "httpResponse.h"
#include "user.h"
#include "httpStatusCodes.h"
#include "modelPqxx.h"
class controller {
public:
    static std::string compress_gzip(const std::string& str,int compressionLevel);
    static std::stringstream stringifyResponse(const httpResponse &response);
    static user getUserValuesFromRequest(httpRequest &request);
    static bool checkForCredentials(const std::string &username, const std::string &password);
    static bool checkIfAuth(httpRequest &request);
    static bool getUserByUsername(const std::string &username);
    static bool insertNewNonExistantUser(user newUser);
};


#endif //C_BACKEND_CONTROLLER_H
