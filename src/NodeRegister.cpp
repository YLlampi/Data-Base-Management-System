#include "NodeRegister.h"

NodeRegister::NodeRegister() {

}

NodeRegister::NodeRegister(std::list<std::string> &valores, int idGeneral) {
    this->valoresColumnas = valores;
    this->id_general = idGeneral;
    //this->id = std::atoi(&this->valoresColumnas.front()[0]);
    this->id = valores.front();
}

std::string NodeRegister::getId() const {
    return id;
}

int NodeRegister::getIdGeneral() const {
    return id_general;
}

const std::list<std::string> &NodeRegister::getValoresColumnas() const {
    return valoresColumnas;
}

void NodeRegister::setValoresColumnas(const std::list<std::string> &valoresColumnas) {
    NodeRegister::valoresColumnas = valoresColumnas;
}
