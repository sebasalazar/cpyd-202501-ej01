#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
#include <ctime>

class Persona {
public:
    Persona();
    Persona(const Persona& orig);
    virtual ~Persona();
    std::string GetApellidos() const;
    void SetApellidos(std::string apellidos);
    std::tm GetFechaNacimiento() const;
    void SetFechaNacimiento(std::tm fechaNacimiento);
    long GetId() const;
    void SetId(long id);
    std::string GetNombres() const;
    void SetNombres(std::string nombres);
    long GetRut() const;
    void SetRut(long rut);

private:
    long id;
    long rut;
    std::string nombres;
    std::string apellidos;
    std::tm fechaNacimiento;
};

#endif /* PERSONA_H */

