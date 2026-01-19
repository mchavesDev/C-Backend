//
// Created by mario on 17/1/26.
//

#include "../headers/modelPqxx.h"

modelPqxx::modelPqxx(const std::string &connUrl) {
    this->connUrl=connUrl;
}

auto modelPqxx::selectPqxx(const std::string& table,const std::string rows[]) {
    pqxx::connection con{this->connUrl};
    pqxx::work tx{con};
    std::string query = "SELECT " + table + " FROM ";

    int i=0;
    while (i<rows->length()) {
        query += rows[i];
        if (i<rows->length()-1) {
            query += ", ";
        } else {
            query += ";";
        }
        i++;
    }
    pqxx::result res = tx.exec(query);
    return res;
}
auto modelPqxx::updatePqxx(const std::string& table, std::string rows[],std::string values[]) {
    pqxx::connection con{this->connUrl};
    pqxx::work tx{con};
    std::string query = "UPDATE " + table + " SET " + rows[0] + " = ";
    int i=0;
    while (i<rows->length()) {
        query += rows[i];
        if (i<rows->length()-1) {
            query += ", ";
        }
        i++;
    }

}
