#include "ServicioBD.h"
#include "Opcional.h"

ServicioBD::ServicioBD() {
    try {
        std::string connStr("host=159.223.200.213 user=cpyd dbname=cpyddb password=CPyD.2025 sslmode=allow");
        conn = new pqxx::connection(connStr);
        if (!conn->is_open()) {
            throw std::runtime_error("No se pudo establecer la conexión a la base de datos.");
        }
        std::cout << "Conexión exitosa a la base de datos: " << conn->dbname() << std::endl;
    } catch (const std::exception &e) {
        throw std::runtime_error("Error al conectar: " + std::string(e.what()));
    }
}

ServicioBD::ServicioBD(const std::string &connStr) {
    try {
        conn = new pqxx::connection(connStr);
        if (!conn->is_open()) {
            throw std::runtime_error("No se pudo establecer la conexión a la base de datos.");
        }
        std::cout << "Conexión exitosa a la base de datos: " << conn->dbname() << std::endl;
    } catch (const std::exception &e) {
        throw std::runtime_error("Error al conectar: " + std::string(e.what()));
    }
}

ServicioBD::~ServicioBD() {
    if (conn) {
        conn->close();
        delete conn;
    }
}

bool ServicioBD::createPersona(long rut, const std::string &firstname, const std::string &lastname, const std::string &birthdate) {
    try {
        pqxx::work txn(*conn);
        // Se asume que los campos 'id' (y en caso de existir campos con valores por defecto) son manejados automáticamente.
        std::string sql = "INSERT INTO persons (rut, firstname, lastname, birthdate) VALUES ("
                + txn.quote(rut) + ", "
                + txn.quote(firstname) + ", "
                + txn.quote(lastname) + ", "
                + txn.quote(birthdate) + ");";
        txn.exec(sql);
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error al insertar persona: " << e.what() << std::endl;
        return false;
    }
}

Opcional<Persona> ServicioBD::getPersonaById(long id) {
    Opcional<Persona> opt;
    try {
        pqxx::nontransaction ntx(*conn);
        std::string sql = "SELECT pk, rut, firstname, lastname, birthdate, created, updated FROM persons WHERE id = "
                + ntx.quote(id) + ";";
        pqxx::result r = ntx.exec(sql);
        if (r.size() == 1) {
            auto row = r[0];
            Persona p;
            p.SetId(row["pk"].as<long>());
            p.SetRut(row["rut"].as<long>());
            p.SetNombres(row["firstname"].c_str());
            p.SetApellidos(row["lastname"].c_str());
            p.SetFechaNacimiento(parsear_fecha(row["birthdate"].c_str()));
            p.SetCreacion(parsear_fecha(row["created"].c_str()));
            p.SetActualizacion(parsear_fecha(row["updated"].c_str()));
            opt = Opcional<Persona>(p);
        }
    } catch (const std::exception &e) {
        throw std::runtime_error("Error al obtener persona: " + std::string(e.what()));
    }
    return opt;
}

Opcional<Persona> ServicioBD::getPersonaByRut(long rut) {
    Opcional<Persona> opt;
    try {
        pqxx::nontransaction ntx(*conn);
        std::string sql = "SELECT pk, rut, firstname, lastname, birthdate, created, updated FROM persons WHERE rut = "
                + ntx.quote(rut) + ";";
        pqxx::result r = ntx.exec(sql);
        if (r.size() == 1) {
            auto row = r[0];
            Persona p;
            p.SetId(row["pk"].as<long>());
            p.SetRut(row["rut"].as<long>());
            p.SetNombres(row["firstname"].c_str());
            p.SetApellidos(row["lastname"].c_str());
            p.SetFechaNacimiento(parsear_fecha(row["birthdate"].c_str()));
            p.SetCreacion(parsear_fecha(row["created"].c_str()));
            p.SetActualizacion(parsear_fecha(row["updated"].c_str()));
            opt = Opcional<Persona>(p);
        }
    } catch (const std::exception &e) {
        throw std::runtime_error("Error al obtener persona: " + std::string(e.what()));
    }
    return opt;
}

std::vector<Persona> ServicioBD::getAllPersonas() {
    std::vector<Persona> personas;
    try {
        pqxx::nontransaction ntx(*conn);
        pqxx::result r = ntx.exec("SELECT pk, rut, firstname, lastname, birthdate, created, updated FROM persons");
        for (const auto &row : r) {
            Persona p;
            p.SetId(row["pk"].as<long>());
            p.SetRut(row["rut"].as<long>());
            p.SetNombres(row["firstname"].c_str());
            p.SetApellidos(row["lastname"].c_str());
            p.SetFechaNacimiento(parsear_fecha(row["birthdate"].c_str()));
            p.SetCreacion(parsear_fecha(row["created"].c_str()));
            p.SetActualizacion(parsear_fecha(row["updated"].c_str()));
            personas.push_back(p);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error al obtener la lista de personas: " << e.what() << std::endl;
    }
    return personas;
}

bool ServicioBD::updatePersona(long rut, const std::string &firstname, const std::string &lastname, const std::string &birthdate) {
    try {
        pqxx::work txn(*conn);
        std::string sql = "UPDATE persons SET "
                "firstname = " + txn.quote(firstname) + ", "
                "lastname = " + txn.quote(lastname) + ", "
                "birthdate = " + txn.quote(birthdate) +
                " WHERE rut = " + txn.quote(rut) + ";";
        txn.exec(sql);
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error al actualizar persona: " << e.what() << std::endl;
        return false;
    }
}

bool ServicioBD::deletePersona(long id) {
    try {
        pqxx::work txn(*conn);
        std::string sql = "DELETE FROM persons WHERE pk = " + txn.quote(id) + ";";
        txn.exec(sql);
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error al eliminar persona: " << e.what() << std::endl;
        return false;
    }
}
