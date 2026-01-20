//
// Created by mario on 17/1/26.
//

#include "../headers/modelPqxx.h"

modelPqxx::modelPqxx(const std::string &connUrl) {
    this->connUrl=connUrl;
    this->Query="";
}
// main queries
void modelPqxx::selectPqxx(const std::string& table,const std::string rows[], int numRows) {

    std::string query = "SELECT ";

    int i=0;
    while (i<numRows) {
        query += rows[i];
        if (i<numRows-1 && numRows>1) {
            query += ", ";
        }
        i++;
    }
    query += " FROM " + table + " ";

    this->Query = query;
}
void modelPqxx::updatePqxx(const std::string &table, const std::string rows[],const std::string values[],int numRows){
    pqxx::connection con{this->connUrl};
    pqxx::work tx{con};
    std::string query = "UPDATE " + table + " SET ";
    int rowsIncr=0;
    while (rowsIncr<numRows) {
        query += rows[rowsIncr];
        if (rowsIncr<numRows-1) {
            query += ", ";
        }
        rowsIncr++;
    }
    int valuesIncr = 0;
    while (valuesIncr<numRows) {
        query += values[valuesIncr];
        if (valuesIncr<numRows-1) {
            query += ", ";
        }
        valuesIncr++;
    }
    this->Query = query;
}
// particles


void modelPqxx::wherePqxx( const std::string rows[],const std::string values[],int numRows) {
    // values need the operator symbol in string
    std::string query ="WHERE ";//= " WHERE " + rows[0] + values[0];
    int rowsIncr = 0;
    while (rowsIncr<numRows) {
        query += rows[rowsIncr]+ " " + values[rowsIncr];
        if (rowsIncr<numRows-1) {
            query += ", ";
        }
        rowsIncr++;
    }
    this->Query += query;
}

pqxx::result modelPqxx::executePqxx() {
    pqxx::connection con{this->connUrl};
    pqxx::work tx(con);
    this->Query+=";";
    pqxx::result res = tx.exec(this->Query);
    tx.commit();
    return res;
}

