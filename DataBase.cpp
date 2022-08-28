#include "DataBase.h"

DataBase::DataBase() {

}

DataBase::DataBase(std::string nombre, int id) {
    this->nombre = nombre;
    this->id_database = id;
    this->contTables = 0;
    this->tables = new std::list<Table>();
}

void DataBase::addTable(Table newTable) {
    this->tables->push_back(newTable);
    this->contTables++;
}

const std::string &DataBase::getNombre() const {
    return nombre;
}

int DataBase::getContTables() const {
    return contTables;
}

int DataBase::getIdDatabase() const {
    return this->id_database;
}

std::list<Table> *DataBase::getTables() const {
    return tables;
}


