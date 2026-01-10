//
// Created by mario on 10/1/26.
//


#ifndef C_BACKEND_ROUTER_H
#define C_BACKEND_ROUTER_H
#include <memory>

#include "httpRequest.h"
const std::map<std::string,int> endpoints = {
    {"/api",0},
    {"/",0},
    {"/login",0},
    {"/user",1}};
int parseRequest(const std::unique_ptr<httpRequest> &request);
#endif //C_BACKEND_ROUTER_H