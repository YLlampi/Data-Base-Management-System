#ifndef DATA_BASE_MANAGEMENT_SYSTEM_NODEREGISTER_H
#define DATA_BASE_MANAGEMENT_SYSTEM_NODEREGISTER_H

#include <bits/stdc++.h>

class NodeRegister {
private:
    std::string id;
    int id_general;
    std::list<std::string> valoresColumnas;
public:
    NodeRegister();
    NodeRegister(std::list<std::string> &, int);

    std::string getId() const;

    int getIdGeneral() const;

    const std::list<std::string> &getValoresColumnas() const;

    void setValoresColumnas(const std::list<std::string> &valoresColumnas);
};


#endif //DATA_BASE_MANAGEMENT_SYSTEM_NODEREGISTER_H
