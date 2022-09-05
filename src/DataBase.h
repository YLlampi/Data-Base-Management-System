#ifndef DATA_BASE_MANAGEMENT_SYSTEM_DATABASE_H
#define DATA_BASE_MANAGEMENT_SYSTEM_DATABASE_H

#include "Table.h"

class DataBase {
private:
    std::string nombre;
    int id_database;
    std::list<Table> *tables;
    int contTables;

public:
    DataBase();
    DataBase(std::string, int);

    void addTable(Table);

    const std::string &getNombre() const;


    int getContTables() const;

    std::list<Table> *getTables() const;

    int getIdDatabase() const;
};


#endif //DATA_BASE_MANAGEMENT_SYSTEM_DATABASE_H
