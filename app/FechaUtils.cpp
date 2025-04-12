#include "FechaUtils.h"

std::tm parsear(const std::string& fechaStr) {
    std::tm fecha = {};
    std::istringstream iss(fechaStr);
    if (!(iss >> std::get_time(&fecha,"%Y-%m-%d"))) {
        std::cerr << "El formato de fecha es incorrecto" << std::endl;
    }
    return fecha;
}

std::string formatear(std::tm& fecha) {
    std::ostringstream oss;
    oss << std::put_time(&fecha,"%Y-%m-%d");
    return oss.str();
}