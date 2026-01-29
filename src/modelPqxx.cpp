//
// Created by mario on 17/1/26.
//

#include "../headers/modelPqxx.h"

modelPqxx::modelPqxx(const std::string &connUrl) {
    this->connUrl=connUrl;

    this->Query="";
}
// main queries
void modelPqxx::selectPqxx(const std::string& table,const std::string cols[], int numCols) {
    std::string query = "SELECT ";
    int i=0;
    while (i<numCols) {
        query += cols[i];
        if (i<numCols-1 && numCols>1) {
            query += ", ";
        }
        i++;
    }

    query += " FROM " + table + " ";
    this->Query = query;
}
void modelPqxx::updatePqxx(const std::string &table, const std::string cols[],const std::string values[],int numRows){
    pqxx::connection con{this->connUrl};
    pqxx::work tx{con};
    std::string query = "UPDATE " + table + " SET ";
    int rowsIncr=0;
    while (rowsIncr<numRows) {
        query += cols[rowsIncr];
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
/**
 * Insert particle
 */
void modelPqxx::insertPqxx(const std::string &table,const std::string cols[],const std::string values[],int numCols) {
    // values need the operator symbol in string
    std::string query ="INSERT INTO "+table+" (";
    std::string valuesApp = ") VALUES (";
    int colsIncr = 0;
    while (colsIncr<numCols) {
        this->Params.append(values[colsIncr]);
        size_t paramsCount = this->Params.size();
        query +=  cols[colsIncr] ;
        valuesApp += "$"+std::to_string(paramsCount);
        if (colsIncr<numCols-1) {
            query += ", ";
            valuesApp += ", ";
        }
        colsIncr++;
    }
    this->Query += query + valuesApp + ")";
}
/**
 * Where particle args colums to compare and values to compare to, also number of columns
 */
// particles
void modelPqxx::wherePqxx( const std::string cols[],const std::string values[],int numCols) {
    // values need the operator symbol in string
    std::string query ="WHERE ";
    int colsIncr = 0;
    while (colsIncr<numCols) {
        this->Params.append(values[colsIncr]);
        size_t paramsCount = this->Params.size();
        query +=  cols[colsIncr] + "= " + "$"+std::to_string(paramsCount);
        if (colsIncr<numCols-1) {
            query += " AND ";
        }
        colsIncr++;
    }
    this->Query += query;
}
/**
 * Execute command to parametrize and send queries
 */
pqxx::result modelPqxx::executePqxx() {
    pqxx::connection con{this->connUrl};
    this->Query+=";";
    std::string &query = this->Query;
    const pqxx::params parms= this->Params;
    pqxx::work tx(con);
    pqxx::result res = tx.exec(query,parms);
    tx.commit();
    return res;
}