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
    /**
     * Constructor for new user without entry on db
     */
    user(const std::string &username, const std::string &password);
    /**
    * Constructor for existing user in db
    */
    user(int id, const std::string &username, const std::string &password, const std::string &token);
    int getUserId() const;
    std::string getUsername();
    std::string getPassword();
    std::string getToken();
    void setUserId(const int id);
    void setUsername(const std::string &username);
    void setPassword(const std::string &password);
    void setToken(const std::string &token);

};



#endif //C_BACKEND_USER_H