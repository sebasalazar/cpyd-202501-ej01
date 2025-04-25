#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <stdexcept>
#include <cctype>

std::tm parsear_fecha(const std::string& fechaStr);

std::string formatear_fecha(std::tm& fecha);

std::string limpiarRut(const std::string &rut);

char calcularDigitoVerificador(const std::string &numero);

bool validarRut(const std::string &rut);

std::string formatearRut(const std::string &rut);

long obtenerRutNumerico(const std::string &rut);

#endif // UTILIDADES_H
