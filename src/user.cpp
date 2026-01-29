//
// Created by mario on 17/1/26.
//

#include "../headers/user.h"

user::user(const std::string &username, const std::string &password) {
    this->setUsername(username);
    this->setPassword(password);
}

user::user(const int id, const std::string &username, const std::string &password, const std::string &token) {
    this->setUsername(username);
    this->setPassword(password);
    this->setUserId(id);
    this->setToken(token);
}

int user::getUserId() const {
    return this->Id;
}

void user::setUserId(const int id) {
    this->Id=id;
}

std::string user::getUsername() {
    return this->Username;
}

std::string user::getPassword() {
    return this->Password;

}

std::string user::getToken() {
    return this->Token;

}

void user::setUsername(const std::string &username) {
    this->Username=username;
}

void user::setPassword(const std::string &password) {
    this->Password=password;

}

void user::setToken(const std::string &token) {
    this->Token=token;

}
