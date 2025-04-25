#include "ServicioBD.h"

ServicioBD::ConnectionPool::ConnectionPool(std::size_t maxSize, const std::string& connStr)
: maxSize(maxSize), connectionString(connStr) {
    for (std::size_t i = 0; i < maxSize; ++i) {
        std::shared_ptr<pqxx::connection> conn = std::make_shared<pqxx::connection>(connectionString);
        pool.push(conn);
    }
}

std::shared_ptr<pqxx::connection> ServicioBD::ConnectionPool::acquire() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() -> bool {
        return !pool.empty(); });

    std::shared_ptr<pqxx::connection> conn = pool.front();
    pool.pop();

    if (!conn->is_open()) {
        conn = std::make_shared<pqxx::connection>(connectionString);
    }

    return conn;
}

void ServicioBD::ConnectionPool::release(std::shared_ptr<pqxx::connection> conn) {
    if (conn && conn->is_open()) {
        std::unique_lock<std::mutex> lock(mtx);
        pool.push(conn);
        lock.unlock();
        cv.notify_one();
    }
}

ServicioBD::ServicioBD() :
connectionPool(std::make_unique<ConnectionPool>(10, "host=159.223.200.213 user=cpyd dbname=cpyddb password=CPyD.2025 sslmode=allow")) {
}

ServicioBD::ServicioBD(const std::string& connStr, std::size_t poolSize)
: connectionPool(std::make_unique<ConnectionPool>(poolSize, connStr)) {
}

template<typename Func>
auto ServicioBD::usarConexion(Func&& f) -> decltype(f(std::declval<pqxx::connection&>())) {
    std::shared_ptr<pqxx::connection> conn = connectionPool->acquire();
    try {
        auto resultado = f(*conn);
        connectionPool->release(conn);
        return resultado;
    } catch (...) {
        connectionPool->release(conn);
        throw;
    }
}

// --------- CRUD ---------

bool ServicioBD::createPersona(long rut, const std::string& firstname, const std::string& lastname, const std::tm& birthdate) {
    return usarConexion([&](pqxx::connection & conn) -> bool {
        pqxx::work txn(conn);
        std::string query = "INSERT INTO persons (rut, firstname, lastname, birthdate) VALUES (" +
                txn.quote(rut) + ", " +
                txn.quote(firstname) + ", " +
                txn.quote(lastname) + ", " +
                txn.quote(formatear_fecha(birthdate)) + ")";
        txn.exec(query);
        txn.commit();
        return true;
    });
}

Opcional<Persona> ServicioBD::getPersonaById(long id) {
    return usarConexion([&](pqxx::connection & conn) -> Opcional<Persona> {
        pqxx::work txn(conn);
        std::string query = "SELECT id, rut, firstname, lastname, birthdate FROM persons WHERE id = " + txn.quote(id);
        pqxx::result r = txn.exec(query);
        txn.commit();

        if (r.empty()) {
            return Opcional<Persona>();
        } else {
            const pqxx::row& fila = r[0];
                    Persona p(
                    fila["id"].as<long>(),
                    fila["rut"].as<long>(),
                    fila["firstname"].as<std::string>(),
                    fila["lastname"].as<std::string>(),
                    fila["birthdate"].as<std::string>()
                    );
            return Opcional<Persona>(p);
        }
    });
}

Opcional<Persona> ServicioBD::getPersonaByRut(long rut) {
    return usarConexion([&](pqxx::connection & conn) -> Opcional<Persona> {
        pqxx::work txn(conn);
        std::string query = "SELECT id, rut, firstname, lastname, birthdate FROM persons WHERE rut = " + txn.quote(rut);
        pqxx::result r = txn.exec(query);
        txn.commit();

        if (r.empty()) {
            return Opcional<Persona>();
        } else {
            const pqxx::row& fila = r[0];
                    Persona p(
                    fila["id"].as<long>(),
                    fila["rut"].as<long>(),
                    fila["firstname"].as<std::string>(),
                    fila["lastname"].as<std::string>(),
                    fila["birthdate"].as<std::string>()
                    );
            return Opcional<Persona>(p);
        }
    });
}

std::vector<Persona> ServicioBD::getAllPersonas() {
    return usarConexion([&](pqxx::connection & conn) -> std::vector<Persona> {
        pqxx::work txn(conn);
        std::string query = "SELECT id, rut, firstname, lastname, birthdate FROM persons";
        pqxx::result r = txn.exec(query);
        txn.commit();

        std::vector<Persona> personss;
        for (pqxx::result::const_iterator it = r.begin(); it != r.end(); ++it) {
            const pqxx::row& fila = *it;
                    Persona p(
                    fila["id"].as<long>(),
                    fila["rut"].as<long>(),
                    fila["firstname"].as<std::string>(),
                    fila["lastname"].as<std::string>(),
                    fila["birthdate"].as<std::string>()
                    );
                    personss.push_back(p);
        }
        return personss;
    });
}

bool ServicioBD::updatePersona(long id, const std::string& firstname, const std::string& lastname, const std::string& birthdate) {
    return usarConexion([&](pqxx::connection & conn) -> bool {
        pqxx::work txn(conn);
        std::string query = "UPDATE persons SET firstname = " + txn.quote(firstname) +
                ", lastname = " + txn.quote(lastname) +
                ", birthdate = " + txn.quote(birthdate) +
                " WHERE id = " + txn.quote(id);
        txn.exec(query);
        txn.commit();
        return true;
    });
}

bool ServicioBD::deletePersona(long id) {
    return usarConexion([&](pqxx::connection & conn) -> bool {
        pqxx::work txn(conn);
        std::string query = "DELETE FROM persons WHERE id = " + txn.quote(id);
        txn.exec(query);
        txn.commit();
        return true;
    });
}
