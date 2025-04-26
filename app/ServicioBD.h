#ifndef SERVICIO_BD_H
#define SERVICIO_BD_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "Opcional.h"
#include "Persona.h"

class ServicioBD {
public:
    ServicioBD();
    explicit ServicioBD(const std::string& connStr, std::size_t poolSize = 10);


    // Operaciones CRUD:
    // CREATE: Inserta una nueva persona.
    bool createPersona(const long rut, const std::string& firstname, const std::string& lastname, const std::tm& birthdate);
    // READ: Obtiene una persona por su RUT.
    Opcional<Persona> getPersonaByRut(const long rut);
    // READ: Obtiene todas las personas.
    std::vector<Persona> getAllPersonas();
    // UPDATE: Actualiza los datos de una persona.
    bool updatePersona(const long rut, const std::string& firstname, const std::string& lastname, const std::tm& birthdate);
    // DELETE: Elimina una persona.
    bool deletePersona(const long rut);

private:

    class ConnectionPool {
    private:
        std::queue<std::shared_ptr<pqxx::connection>> pool;
        std::mutex mtx;
        std::condition_variable cv;
        std::size_t maxSize;
        std::string connectionString;

    public:
        ConnectionPool(std::size_t maxSize, const std::string& connStr);
        std::shared_ptr<pqxx::connection> acquire();
        void release(std::shared_ptr<pqxx::connection> conn);
    };

    std::unique_ptr<ConnectionPool> connectionPool;

    template<typename Func>
    auto usarConexion(Func&& f) -> decltype(f(std::declval<pqxx::connection&>()));
};

#endif // SERVICIO_BD_H
