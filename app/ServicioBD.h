#ifndef SERVICIO_BD_H
#define SERVICIO_BD_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include "Persona.h"

class ServicioBD {
public:
    ServicioBD();
    // Constructor: establece la conexión a la base de datos.
    ServicioBD(const std::string &connStr);
    // Destructor: cierra la conexión y libera memoria.
    ~ServicioBD();

    // Operaciones CRUD:
    // CREATE: Inserta una nueva persona.
    bool createPersona(long rut, const std::string &firstname, const std::string &lastname, const std::string &birthdate);
    // READ: Obtiene una persona por su ID.
    Persona getPersonaById(long id);
    // READ: Obtiene todas las personas.
    std::vector<Persona> getAllPersonas();
    // UPDATE: Actualiza los datos de una persona.
    bool updatePersona(long id, const std::string &firstname, const std::string &lastname, const std::string &birthdate);
    // DELETE: Elimina una persona.
    bool deletePersona(long id);

private:
    pqxx::connection *conn; // Puntero a la conexión con la BD.
};

#endif // SERVICIO_BD_H
