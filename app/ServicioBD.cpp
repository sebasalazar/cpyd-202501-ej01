#include "ServicioBD.h"

ServicioBD::ServicioBD() {
    try {
        conn = new pqxx::connection(connStr);
        if (!conn->is_open()) {
            throw runtime_error("No se pudo establecer la conexión a la base de datos.");
        }
        cout << "Conexión exitosa a la base de datos: " << conn->dbname() << endl;
    } catch (const exception &e) {
        throw runtime_error("Error al conectar: " + string(e.what()));
    }
}

ServicioBD::ServicioBD(const std::string &connStr) {
    try {
        conn = new pqxx::connection(connStr);
        if (!conn->is_open()) {
            throw runtime_error("No se pudo establecer la conexión a la base de datos.");
        }
        cout << "Conexión exitosa a la base de datos: " << conn->dbname() << endl;
    } catch (const exception &e) {
        throw runtime_error("Error al conectar: " + string(e.what()));
    }
}

ServicioBD::~ServicioBD() {
    if (conn) {
        conn->disconnect();
        delete conn;
    }
}

bool ServicioBD::createPersona(long rut, const std::string &firstname, const std::string &lastname, const std::string &birthdate) {
    try {
        pqxx::work txn(*conn);
        // Se asume que los campos 'id' (y en caso de existir campos con valores por defecto) son manejados automáticamente.
        std::string sql = "INSERT INTO persona (rut, firstname, lastname, birthdate) VALUES ("
                + txn.quote(rut) + ", "
                + txn.quote(firstname) + ", "
                + txn.quote(lastname) + ", "
                + txn.quote(birthdate) + ");";
        txn.exec(sql);
        txn.commit();
        return true;
    } catch (const exception &e) {
        cerr << "Error al insertar persona: " << e.what() << endl;
        return false;
    }
}

Persona ServicioBD::getPersonaById(long id) {
    Persona p;
    try {
        pqxx::nontransaction ntx(*conn);
        std::string sql = "SELECT id, rut, firstname, lastname, birthdate FROM persona WHERE id = "
                + ntx.quote(id) + ";";
        pqxx::result r = ntx.exec(sql);
        if (r.size() != 1) {
            throw runtime_error("Persona no encontrada o se encontraron múltiples registros.");
        }
        auto row = r[0];
        p.id = row["id"].as<long>();
        p.rut = row["rut"].as<long>();
        p.firstname = row["firstname"].c_str();
        p.lastname = row["lastname"].c_str();
        p.birthdate = row["birthdate"].c_str();
    } catch (const exception &e) {
        throw runtime_error("Error al obtener persona: " + string(e.what()));
    }
    return p;
}

std::vector<Persona> ServicioBD::getAllPersonas() {
    std::vector<Persona> personas;
    try {
        pqxx::nontransaction ntx(*conn);
        pqxx::result r = ntx.exec("SELECT id, rut, firstname, lastname, birthdate FROM persona;");
        for (const auto &row : r) {
            Persona p;
            p.id = row["id"].as<long>();
            p.rut = row["rut"].as<long>();
            p.firstname = row["firstname"].c_str();
            p.lastname = row["lastname"].c_str();
            p.birthdate = row["birthdate"].c_str();
            personas.push_back(p);
        }
    } catch (const exception &e) {
        cerr << "Error al obtener la lista de personas: " << e.what() << endl;
    }
    return personas;
}

bool ServicioBD::updatePersona(long id, const std::string &firstname, const std::string &lastname, const std::string &birthdate) {
    try {
        pqxx::work txn(*conn);
        std::string sql = "UPDATE persona SET "
                "firstname = " + txn.quote(firstname) + ", "
                "lastname = " + txn.quote(lastname) + ", "
                "birthdate = " + txn.quote(birthdate) +
                " WHERE id = " + txn.quote(id) + ";";
        txn.exec(sql);
        txn.commit();
        return true;
    } catch (const exception &e) {
        cerr << "Error al actualizar persona: " << e.what() << endl;
        return false;
    }
}

bool ServicioBD::deletePersona(long id) {
    try {
        pqxx::work txn(*conn);
        std::string sql = "DELETE FROM persona WHERE id = " + txn.quote(id) + ";";
        txn.exec(sql);
        txn.commit();
        return true;
    } catch (const exception &e) {
        cerr << "Error al eliminar persona: " << e.what() << endl;
        return false;
    }
}
