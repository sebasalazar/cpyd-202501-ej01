#ifndef FECHA_UTILS_H
#define FECHA_UTILS_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

std::tm parsear(const std::string& fechaStr);

std::string formatear(std::tm& fecha);

#endif // FECHA_UTILS_H
