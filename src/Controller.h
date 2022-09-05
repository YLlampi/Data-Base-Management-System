#ifndef DATA_BASE_MANAGEMENT_SYSTEM_CONTROLLER_H
#define DATA_BASE_MANAGEMENT_SYSTEM_CONTROLLER_H


#include "DataBase.h"
#include "NodeRegister.h"


/*
 * Clase que hace como funcion principal
 * Administra todo el sistema
 * Almacena todos los registros(disco)
 */
class Controller {
private:

    int contDataBases;
    std::list<DataBase> databases;
    std::vector<NodeRegister> totalRegisters; // Disk
    int contRegisters;
public:
    Controller();

    void menu();

    void crearBaseDeDatos();

    void agregarTabla();

    void agregarRegistro();

    void eliminarRegistro();

    void mostrarRegistros();

    void ActualizarRegistro();

    void clearScreen();

    void printlines(int encabezado);
};


#endif //DATA_BASE_MANAGEMENT_SYSTEM_CONTROLLER_H
