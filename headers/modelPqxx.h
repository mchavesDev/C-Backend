//
// Created by mario on 17/1/26.
//

#ifndef C_BACKEND_MODELPQXX_H
#define C_BACKEND_MODELPQXX_H
#include <pqxx/pqxx>

class modelPqxx {
    public:
    std::string connUrl;
    modelPqxx(const std::string &connUrl);
    auto selectPqxx(const std::string &table, const std::string rows[]);
    auto updatePqxx(const std::string& table, std::string rows[],std::string values[]);
};


#endif //C_BACKEND_MODELPQXX_H