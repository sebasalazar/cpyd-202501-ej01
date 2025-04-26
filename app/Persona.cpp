#include "Persona.h"

// Constructor por defecto usando lista de inicializadores

Persona::Persona()
: id(0), rut(0), nombres(""), apellidos(""),
fechaNacimiento({}), creacion({}), actualizacion({}) {
}

// Constructor parametrizado usando funciones de conversión de "Utilidades.h"

Persona::Persona(const std::string& rut,
        const std::string& nombres,
        const std::string& apellidos,
        const std::string& fechaNacimiento)
: id(0),
rut(obtenerRutNumerico(rut)),
nombres(nombres),
apellidos(apellidos),
fechaNacimiento(parsear_fecha(fechaNacimiento)),
creacion({}),
actualizacion({}) {
}

Persona::Persona(const long& id,
        const long& rut,
        const std::string& nombres,
        const std::string& apellidos,
        const std::string& fechaNacimiento,
        const std::string& fechaCreacion,
        const std::string& fechaActualizacion)
: id(id),
rut(rut),
nombres(nombres),
apellidos(apellidos),
fechaNacimiento(parsear_fecha(fechaNacimiento)),
creacion(parsear_fecha(fechaCreacion)),
actualizacion(parsear_fecha(fechaActualizacion)) {
}

// Constructor de copia

Persona::Persona(const Persona& orig)
: id(orig.id),
rut(orig.rut),
nombres(orig.nombres),
apellidos(orig.apellidos),
fechaNacimiento(orig.fechaNacimiento),
creacion(orig.creacion),
actualizacion(orig.actualizacion) {
}

Persona::~Persona() {
}

std::string Persona::GetApellidos() const {
    return apellidos;
}

void Persona::SetApellidos(const std::string& apellidos) {
    this->apellidos = apellidos;
}

std::tm Persona::GetFechaNacimiento() const {
    return fechaNacimiento;
}

void Persona::SetFechaNacimiento(const std::tm& fechaNacimiento) {
    this->fechaNacimiento = fechaNacimiento;
}

long Persona::GetId() const {
    return id;
}

void Persona::SetId(long id) {
    this->id = id;
}

std::string Persona::GetNombres() const {
    return nombres;
}

void Persona::SetNombres(const std::string& nombres) {
    this->nombres = nombres;
}

long Persona::GetRut() const {
    return rut;
}

void Persona::SetRut(long rut) {
    this->rut = rut;
}

std::tm Persona::GetActualizacion() const {
    return actualizacion;
}

void Persona::SetActualizacion(const std::tm& actualizacion) {
    this->actualizacion = actualizacion;
}

std::tm Persona::GetCreacion() const {
    return creacion;
}

void Persona::SetCreacion(const std::tm& creacion) {
    this->creacion = creacion;
}
