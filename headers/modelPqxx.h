//
// Created by mario on 17/1/26.
//

#ifndef C_BACKEND_MODELPQXX_H
#define C_BACKEND_MODELPQXX_H
#include <pqxx/pqxx>

class modelPqxx {
    public:
    std::string connUrl;
    std::string Query;
    pqxx::params Params;
    modelPqxx(const std::string &connUrl);
    // queries
    void selectPqxx(const std::string &table, const std::string cols[], int numCols);
    void insertPqxx(const std::string &table, const std::string cols[],const std::string values[],int numCols);
    void updatePqxx(const std::string &table, const std::string cols[],const std::string values[], int numRows);
    void wherePqxx(const std::string cols[],const std::string values[], int numCols);
    // execute
    pqxx::result executePqxx();
};


#endif //C_BACKEND_MODELPQXX_H