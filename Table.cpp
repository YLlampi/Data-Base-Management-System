#include "Table.h"

Table::Table() {

}

Table::Table(std::string nombre, std::list<std::string> &encabezados, int id) {
    this->nombre = nombre;
    this->encabezados = encabezados;
    this->id_table = id;
    this->id_register = 0;
    this->bptree = new BPTree(this->MAX_M);
}

int Table::getIdTable() const {
    return id_table;
}

const std::string &Table::getNombre() const {
    return nombre;
}

const std::list<std::string> &Table::getEncabezados() const {
    return encabezados;
}


void Table::addRegister(int id_general) {
    this->bptree->insert(id_general);
    this->id_register++;
}

int Table::getIdRegister() const {
    return this->id_register;
}

BPTree *Table::getBptree() const {
    return bptree;
}




