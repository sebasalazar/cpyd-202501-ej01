#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
#include <ctime>
#include "Utilidades.h"

class Persona {
public:
    Persona();
    Persona(const std::string& rut,
            const std::string& nombres,
            const std::string& apellidos,
            const std::string& fechaNacimiento);
    Persona(const long& id,
            const long& rut,
            const std::string& nombres,
            const std::string& apellidos,
            const std::string& fechaNacimiento,
            const std::string& fechaCreacion,
            const std::string& fechaActualizacion);
    Persona(const Persona& orig);
    virtual ~Persona();

    std::string GetApellidos() const;
    void SetApellidos(const std::string& apellidos);

    std::tm GetFechaNacimiento() const;
    void SetFechaNacimiento(const std::tm& fechaNacimiento);

    long GetId() const;
    void SetId(long id);

    std::string GetNombres() const;
    void SetNombres(const std::string& nombres);

    long GetRut() const;
    void SetRut(long rut);

    std::tm GetActualizacion() const;
    void SetActualizacion(const std::tm& actualizacion);

    std::tm GetCreacion() const;
    void SetCreacion(const std::tm& creacion);

private:
    long id;
    long rut;
    std::string nombres;
    std::string apellidos;
    std::tm fechaNacimiento;
    std::tm creacion;
    std::tm actualizacion;
};

#endif /* PERSONA_H */
