#ifndef DATA_BASE_MANAGEMENT_SYSTEM_TABLE_H
#define DATA_BASE_MANAGEMENT_SYSTEM_TABLE_H

#include "BPTree.h"

class Table {
private:
    const int MAX_M = 4; // value of m(B+Tree)
    int id_table;
    std::string nombre;
    std::list<std::string> encabezados;
    BPTree *bptree;
    int id_register;

public:
    Table();

    Table(std::string, std::list<std::string> &, int);

    int getIdTable() const;

    const std::string &getNombre() const;

    const std::list<std::string> &getEncabezados() const;

    void addRegister(int);

    int getIdRegister() const;

    BPTree *getBptree() const;



    friend class Controller;

};


#endif //DATA_BASE_MANAGEMENT_SYSTEM_TABLE_H