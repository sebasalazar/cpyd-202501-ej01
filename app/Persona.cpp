#include "Persona.h"

Persona::Persona() {
}

Persona::Persona(const Persona& orig) {
}

Persona::~Persona() {
}

std::string Persona::GetApellidos() const {
    return apellidos;
}

void Persona::SetApellidos(std::string apellidos) {
    this->apellidos = apellidos;
}

std::tm Persona::GetFechaNacimiento() const {
    return fechaNacimiento;
}

void Persona::SetFechaNacimiento(std::tm fechaNacimiento) {
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

void Persona::SetNombres(std::string nombres) {
    this->nombres = nombres;
}

long Persona::GetRut() const {
    return rut;
}

void Persona::SetRut(long rut) {
    this->rut = rut;
}
