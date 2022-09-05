#include "Controller.h"
/*
 * Class Controller
 * Clase que administra toda la aplicacion
 */
Controller::Controller() {
    this->contRegisters = 0;
}

void Controller::menu() {
    char opcion = '0';
    do {
        clearScreen();
        std::cout << "Bienvenidos al Sistema Gestor de Base de Datos" << '\n';
        std::cout << "\t:::::: Menu ::::::\t" << '\n';

        std::cout << "1) Crear Base de Datos." << '\n';
        std::cout << "2) Agregar Tabla a una Base de Datos." << '\n';
        std::cout << "3) Agregar Registo a una Tabla." << '\n';
        std::cout << "4) Eliminar Registros de una Tabla." << '\n';
        std::cout << "5) Mostrar Registros de una Tabla." << '\n';
        std::cout << "6) Actualizar Registro de una Tabla." << '\n';
        std::cout << "7) Salir." << '\n';

        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        do {
            if (opcion <= 48 or opcion >= 56) {
                std::cout << "Seleccione una opcion correcta: ";
                std::cin >> opcion;
            } else break;
        } while (true);
        clearScreen();
        switch (opcion) {
            case '1':
                crearBaseDeDatos();
                break;
            case '2':
                agregarTabla();
                break;
            case '3':
                agregarRegistro();
                break;
            case '4':
                eliminarRegistro();
                break;
            case '5':
                mostrarRegistros();
                break;
            case '6':
                ActualizarRegistro();
                break;
            case '7':
                std::cout << "Saliendo... Gracias por su visita" << std::endl;
                std::cout<< "Presione enter para continuar..." << std::endl;
                std::cin.ignore();
                std::cin.ignore();
                break;
        }
    } while (opcion != '7');
}

/*
 * Crea una Base de Datos, luego inserta a la lista de Bases de Datos
 * input: nombre_base_de_datos
 */
void Controller::crearBaseDeDatos() {
    std::cout << "Creando una Base de Datos" << std::endl;
    std::string nombreDataBase;
    std::cout << "Nombre de la Base de Datos: ";
    std::cin >> nombreDataBase;
    this->databases.push_back(DataBase(nombreDataBase, this->contDataBases));
    this->contDataBases++;
    std::cout << "Base de Datos creada" << std::endl;
    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

/*
 * Crea y Agrega una Tabla a una determinada Base de Datos, creada anteriormente
 * Si no existe Base de Datos Creada, termina la funcion
 *
 * input: id_data_base, nombre_tabla, cabeceras de las columnas
 *
 */
void Controller::agregarTabla() {
    if (this->databases.empty()) {
        std::cout << "Primero cree una Base de Datos para agregar Tablas" << std::endl;
        return;
    }
    std::cout << "Agregando Tabla a una Base de Datos" << std::endl;
    std::cout << std::endl;
    std::cout << "Bases de Datos disponibles" << std::endl;
    for (auto i = this->databases.begin(); i != this->databases.end(); i++) {
        std::cout << i->getIdDatabase() << ") " << i->getNombre() << std::endl;
    }

    int idTempDataBase;
    std::cout << "Seleccione la base de datos: ";
    std::cin >> idTempDataBase;

    auto tempDataBase = this->databases.begin();
    advance(tempDataBase, idTempDataBase);



    std::string nombreTabla;
    std::cout << "Nombre de la Tabla: ";
    std::cin >> nombreTabla;

    std::list<std::string> tempEncabezados;
    tempEncabezados.push_back("id"); // El campo id es insertado automaticamente por el
                                     // sistema
    std::string opcionSINO;

    do {
        std::cout << "Agregar Columna [SI/NO]: ";
        std::cin >> opcionSINO;
        if (opcionSINO == "SI" or opcionSINO == "si") {
            std::string nombreTemp;
            std::cout << "Nombre de la Columna: ";
            std::cin >> nombreTemp;
            tempEncabezados.push_back(nombreTemp);

        }
    } while (opcionSINO == "SI" or opcionSINO == "si");


    int idTempTable = tempDataBase->getContTables();

    // Añadimos la tabla creada a la base de datos seleccionada
    tempDataBase->addTable(Table(nombreTabla, tempEncabezados, idTempTable));

    std::cout << "Tabla agregada" << std::endl;

    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

/*
 * Agrega un registro a una tabla de una base de datos.
 * verifica si hay bases de datos creada.
 * verifica si hay tablas creadas en la base de datos.
 * input: valores de los registros.
 * Cada registro se alamacena en el disco, tambien se asigna un idetificador,
 * para la indexacion.
 */
void Controller::agregarRegistro() {
    if (this->databases.empty()) {
        std::cout << "Primero cree una Base de Datos para agregar Tablas" << std::endl;
        return;
    }
    std::cout << "Agregando registro a una Tabla" << std::endl;
    std::cout << "Bases de Datos disponibles" << std::endl;
    for (auto & database : this->databases) {
        std::cout << database.getIdDatabase() << ") " << database.getNombre() << std::endl;
    }

    int idTempDataBase;
    std::cout << "Seleccione la base de datos: ";
    std::cin >> idTempDataBase;

    auto tempDataBase = this->databases.begin();
    std::advance(tempDataBase, idTempDataBase);

    if (tempDataBase->getContTables() == 0) {
        std::cout << "Agregue una tabla primero" << std::endl;
        return;
    }

    std::cout << "Tablas disponibles" << std::endl;
    for (auto & i : *tempDataBase->getTables()) {
        std::cout << i.getIdTable() << ") " << i.getNombre() << std::endl;
    }

    int idTempTable;
    std::cout << "Seleccione una Tabla: ";
    std::cin >> idTempTable;

    auto tempTable = tempDataBase->getTables()->begin();
    std::advance(tempTable, idTempTable);

    std::list<std::string> tempValoresColumnas;

    for (auto i = tempTable->getEncabezados().begin(); i != tempTable->getEncabezados().end(); i++) {
        if (i == tempTable->getEncabezados().begin()) continue;
        std::string valueTempColum;
        std::cout << *i << ": ";
        std::cin >> valueTempColum;
        tempValoresColumnas.push_back(valueTempColum);
    }

    int idTempRegister = tempTable->getIdRegister();
    
    tempValoresColumnas.push_front(std::to_string(idTempRegister));

    NodeRegister tempNodeRegister(tempValoresColumnas, this->contRegisters);


    /* 
     * El registro creado, se añade al disco,
     * y la direccion del registro en disco
     * se almacena en la estructura(B+Tree)
     * para su posterior manipulacion
     */
    // Add disk
    this->totalRegisters.push_back(tempNodeRegister);

    tempTable->addRegister(contRegisters);

    this->contRegisters++;
    std::cout << "Correcto Registro" << std::endl;
    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

/*
 * Elimina registro de una tabla
 * input: id_a_eliminar
 * verifica si existe dato
 */
void Controller::eliminarRegistro() {
    if (this->databases.empty()) {
        std::cout << "Primero cree una Base de Datos para agregar Tablas" << std::endl;
        return;
    }
    std::cout << "Eliminando Registro" << std::endl;
    std::cout << "Bases de Datos disponibles" << std::endl;
    for (auto & database : this->databases) {
        std::cout << database.getIdDatabase() << ") " << database.getNombre() << std::endl;
    }

    int idTempDataBase;
    std::cout << "Seleccione la base de datos: ";
    std::cin >> idTempDataBase;

    auto tempDataBase = this->databases.begin();
    std::advance(tempDataBase, idTempDataBase);


    if (tempDataBase->getContTables() == 0) {
        std::cout << "Agregue una tabla primero" << std::endl;
        return;
    }

    std::cout << "Tablas disponibles" << std::endl;
    for (auto & i : *tempDataBase->getTables()) {
        std::cout << i.getIdTable() << ") " << i.getNombre() << std::endl;
    }

    int idTempTable;
    std::cout << "Seleccione una Tabla: ";
    std::cin >> idTempTable;

    auto tempTable = tempDataBase->getTables()->begin();
    std::advance(tempTable, idTempTable);

    BPTree *tTree = tempTable->getBptree();

    tTree->display(tTree->getRoot());


    std::list<int> tempIndexation = tTree->getIndexation(); // Indices generales

    // Mostrar los encabezados de la tabla
    for (auto tempValue : tempTable->getEncabezados()) {
        std::cout << tempValue << "\t";
    }

    std::cout << std::endl;

    for(auto & totalRegister : this->totalRegisters){
        int tempGeneralID = totalRegister.getIdGeneral();

        auto it = std::find(tempIndexation.begin(), tempIndexation.end(), tempGeneralID);
        if(it != tempIndexation.end()){

            for(auto j = totalRegister.getValoresColumnas().begin(); j != totalRegister.getValoresColumnas().end(); j++){
                std::cout << *j << "\t";
            }
            std::cout << std::endl;
        }
    }
    int idTempRegister;
    std::cout << "Seleccione un ID a eliminar: "; std::cin>>idTempRegister;


    /*
     * Buscamos en la estructura(B+Tree) la direccion(id) del registro que queremos eliminar
     * si se encuentra, se elimina
     * 
     */
    for(int i = 0; i < this->totalRegisters.size(); i++){
        int tempGeneralID = this->totalRegisters[i].getIdGeneral();

        // Busca el id del registro que se desea eliminar
        // En la estructura B+Tree
        auto it = std::find(tempIndexation.begin(), tempIndexation.end(), tempGeneralID);
        if(it != tempIndexation.end()){
            if(this->totalRegisters[i].getId() == std::to_string(idTempRegister)){
                tTree->remove(tempGeneralID);
                auto it3 = this->totalRegisters.begin();
                std::advance(it3, i);
                this->totalRegisters.erase(it3);
                break;
            }
        }

    }
    std::cout << std::endl;
    tTree->clearIndexation();
    std::cout << "Registro Eliminado" << std::endl;
    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

/*
 * Despliega todos los registros de una determinada tabla
 *
 */
void Controller::mostrarRegistros() {
    if (this->databases.empty()) {
        std::cout << "Primero cree una Base de Datos para agregar Tablas" << std::endl;
        return;
    }
    std::cout << "Mostrando Registros" << std::endl;
    std::cout << "Bases de Datos disponibles" << std::endl;
    for (auto & database : this->databases) {
        std::cout << database.getIdDatabase() << ") " << database.getNombre() << std::endl;
    }

    int idTempDataBase;
    std::cout << "Seleccione la base de datos: ";
    std::cin >> idTempDataBase;

    auto tempDataBase = this->databases.begin();
    std::advance(tempDataBase, idTempDataBase);


    if (tempDataBase->getContTables() == 0) {
        std::cout << "Agregue una tabla primero" << std::endl;
        return;
    }

    std::cout << "Tablas disponibles" << std::endl;
    for (auto & i : *tempDataBase->getTables()) {
        std::cout << i.getIdTable() << ") " << i.getNombre() << std::endl;
    }

    int idTempTable;
    std::cout << "Seleccione una Tabla: ";
    std::cin >> idTempTable;

    auto tempTable = tempDataBase->getTables()->begin();
    std::advance(tempTable, idTempTable);

    BPTree *tTree = tempTable->getBptree();

    tTree->display(tTree->getRoot());


    std::list<int> tempIndexation = tTree->getIndexation(); // Indices generales

    int sizeEncabezado = 0;
    std::string auxValue = "";
    int count{0};
    for (auto tempValue : tempTable->getEncabezados()) {
        auxValue += tempValue;
        auxValue += "|\t";
        //std::cout << tempValue << "\t\t";
        count++;
    }
    sizeEncabezado = auxValue.size();
    sizeEncabezado += (count*4);


    //printlines(sizeEncabezado);
    // Mostrar los encabezados de la tabla
    for (auto tempValue : tempTable->getEncabezados()) {
        std::cout << "|" << tempValue << "\t";
    }
    //printlines(sizeEncabezado);

    std::cout << std::endl;

    for(int i = 0; i < this->totalRegisters.size(); i++){
        int tempGeneralID = this->totalRegisters[i].getIdGeneral();

        auto it = std::find(tempIndexation.begin(), tempIndexation.end(), tempGeneralID);
        if(it != tempIndexation.end()){

            for(auto j = this->totalRegisters[i].getValoresColumnas().begin(); j != this->totalRegisters[i].getValoresColumnas().end(); j++){
                std::cout << *j << "\t";
            }
            std::cout << std::endl;
        }

    }
    std::cout << std::endl;

    tTree->clearIndexation();
    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

/*
 * Actualiza valores de un registro
 * input: id_a_actualizar
 * verifica se existe id
 */
void Controller::ActualizarRegistro() {
    if (this->databases.empty()) {
        std::cout << "Primero cree una Base de Datos para agregar Tablas" << std::endl;
        return;
    }
    std::cout << "Actualizando Registro" << std::endl;
    std::cout << "Bases de Datos disponibles" << std::endl;
    for (auto i = this->databases.begin(); i != this->databases.end(); i++) {
        std::cout << i->getIdDatabase() << ") " << i->getNombre() << std::endl;
    }

    int idTempDataBase;
    std::cout << "Seleccione la base de datos: ";
    std::cin >> idTempDataBase;

    auto tempDataBase = this->databases.begin();
    std::advance(tempDataBase, idTempDataBase);


    if (tempDataBase->getContTables() == 0) {
        std::cout << "Agregue una tabla primero" << std::endl;
        return;
    }

    std::cout << "Tablas disponibles" << std::endl;
    for (auto i = tempDataBase->getTables()->begin(); i != tempDataBase->getTables()->end(); i++) {
        std::cout << i->getIdTable() << ") " << i->getNombre() << std::endl;
    }

    int idTempTable;
    std::cout << "Seleccione una Tabla: ";
    std::cin >> idTempTable;

    auto tempTable = tempDataBase->getTables()->begin();
    std::advance(tempTable, idTempTable);

    BPTree *tTree = tempTable->getBptree();

    tTree->display(tTree->getRoot());


    std::list<int> tempIndexation = tTree->getIndexation(); // Indices generales

    // Mostrar los encabezados de la tabla
    for (auto i = tempTable->getEncabezados().begin(); i != tempTable->getEncabezados().end(); i++) {
        std::string tempValue = *i;
        std::cout << tempValue << "\t\t";
    }

    std::cout << std::endl;

    for(int i = 0; i < this->totalRegisters.size(); i++){
        int tempGeneralID = this->totalRegisters[i].getIdGeneral();

        auto it = std::find(tempIndexation.begin(), tempIndexation.end(), tempGeneralID);
        if(it != tempIndexation.end()){

            for(auto j = this->totalRegisters[i].getValoresColumnas().begin(); j != this->totalRegisters[i].getValoresColumnas().end(); j++){
                std::cout << *j << "\t\t";
            }
            std::cout << std::endl;
        }
    }
    int idTempRegister;
    std::cout << "Seleccione un ID a Actualizar: "; std::cin>>idTempRegister;

    for(int i = 0; i < this->totalRegisters.size(); i++){
        int tempGeneralID = this->totalRegisters[i].getIdGeneral();

        auto it = std::find(tempIndexation.begin(), tempIndexation.end(), tempGeneralID);
        if(it != tempIndexation.end()){
            if(this->totalRegisters[i].getId() == std::to_string(idTempRegister)){
                std::cout << "Valores Actuales" << std::endl;
                for (auto j = tempTable->getEncabezados().begin(); j != tempTable->getEncabezados().end(); j++) {
                    std::string tempValue = *j;
                    std::cout << tempValue << "\t\t";
                }
                std::cout << std::endl;

                for(auto j = this->totalRegisters[i].getValoresColumnas().begin(); j != this->totalRegisters[i].getValoresColumnas().end(); j++){
                    std::cout << *j << "\t\t";
                }
                std::cout << std::endl;
                std::cout << "Nuevos Valores" << std::endl;
                std::list<std::string> tempValoresColumnas;
                tempValoresColumnas.push_back(this->totalRegisters[i].getId());
                for (auto j = tempTable->getEncabezados().begin(); j != tempTable->getEncabezados().end(); j++) {
                    if (j == tempTable->getEncabezados().begin()) continue;
                    std::string valueTempColum;
                    std::cout << *j << ": ";
                    std::cin >> valueTempColum;
                    tempValoresColumnas.push_back(valueTempColum);
                }
                this->totalRegisters[i].setValoresColumnas(tempValoresColumnas);
            }
        }

    }
    std::cout << std::endl;
    tTree->clearIndexation();
    std::cout << "Registro Actualizado" << std::endl;
    std::cout<< "Presione enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.ignore();
}

/*
 * Funcion para lipiar pantalla
 */
void Controller::clearScreen() {
    //system("cls");
    std::cout << "\033[2J\033[1;1H";
}

/*
 * Delimitador de encabezados de columnas
 */
void Controller::printlines(int encabezado) {
    std::cout << "\n+";
    for(int i = 0; i < encabezado; i++){
        std::cout << "-";
    }
    std::cout << "+\n";
}
