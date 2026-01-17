//
// Created by mario on 17/1/26.
//

#ifndef C_BACKEND_USER_H
#define C_BACKEND_USER_H
#include <string>


class user {
    public:
        int Id = -1;
        std::string Username;
        std::string Password;
        std::string Token;//probable tokenized hash for session
};



#endif //C_BACKEND_USER_H