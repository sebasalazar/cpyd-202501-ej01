#include "Utilidades.h"

std::tm parsear_fecha(const std::string& fechaStr) {
    std::tm fecha = {};
    std::istringstream iss(fechaStr);
    if (!(iss >> std::get_time(&fecha, "%Y-%m-%d"))) {
        std::cerr << "El formato de fecha es incorrecto" << std::endl;
    }
    return fecha;
}

std::string formatear_fecha(std::tm& fecha) {
    std::ostringstream oss;
    oss << std::put_time(&fecha, "%Y-%m-%d");
    return oss.str();
}

// Función que elimina cualquier carácter que no sea un dígito o la letra 'K'
// y convierte a mayúsculas para normalizar la entrada.

std::string limpiarRut(const std::string &rut) {
    std::string resultado;
    for (char ch : rut) {
        if (std::isdigit(ch) || std::toupper(ch) == 'K') {
            resultado.push_back(std::toupper(ch));
        }
    }
    return resultado;
}

// Función que calcula el dígito verificador (DV) a partir de la parte numérica del RUT.
// Se utiliza la regla del módulo 11: se multiplica cada dígito (de derecha a izquierda)
// por un factor que comienza en 2 y se incrementa cíclicamente hasta 7.

char calcularDigitoVerificador(const std::string &numero) {
    int suma = 0;
    int multiplicador = 2;

    // Recorremos la cadena de dígitos de derecha a izquierda.
    for (int i = numero.size() - 1; i >= 0; i--) {
        int digito = numero[i] - '0';
        suma += digito * multiplicador;
        multiplicador = (multiplicador == 7 ? 2 : multiplicador + 1);
    }

    int resto = suma % 11;
    int dv = 11 - resto;

    if (dv == 11) return '0';
    if (dv == 10) return 'K';
    return '0' + dv;
}

// Función que valida el RUT: limpia la entrada, separa la parte numérica
// y compara el dígito verificador calculado con el proporcionado.

bool validarRut(const std::string &rut) {
    std::string rutLimpio = limpiarRut(rut);
    if (rutLimpio.length() < 2) return false; // Se requiere al menos una parte numérica y el DV

    // La parte numérica es todo excepto el último carácter (que corresponde al DV)
    std::string numero = rutLimpio.substr(0, rutLimpio.size() - 1);
    char dvProporcionado = rutLimpio.back();

    // Verifica que la parte numérica contenga solo dígitos
    for (char c : numero) {
        if (!std::isdigit(c)) return false;
    }

    char dvCalculado = calcularDigitoVerificador(numero);
    return dvCalculado == dvProporcionado;
}

// Función que formatea el RUT de forma legible, insertando puntos cada tres dígitos
// y separando el dígito verificador mediante un guión, por ejemplo: "12345678K" se convierte en "12.345.678-K".

std::string formatearRut(const std::string &rut) {
    std::string rutLimpio = limpiarRut(rut);
    if (rutLimpio.length() < 2) return rut; // Si no es válido, se retorna tal cual

    std::string numero = rutLimpio.substr(0, rutLimpio.size() - 1);
    char dv = rutLimpio.back();
    std::string formateado;

    int contador = 0;
    // Se recorre la parte numérica de derecha a izquierda para insertar los puntos.
    for (int i = numero.size() - 1; i >= 0; i--) {
        formateado.insert(formateado.begin(), numero[i]);
        contador++;
        // Cada tres dígitos (excepto al inicio) se inserta un punto.
        if (contador == 3 && i != 0) {
            formateado.insert(formateado.begin(), '.');
            contador = 0;
        }
    }
    formateado.push_back('-');
    formateado.push_back(dv);

    return formateado;
}

long obtenerRutNumerico(const std::string &rut) {
    if (!validarRut(rut)) {
        throw std::invalid_argument("El RUT proporcionado no es válido.");
    }

    std::string rutLimpio = limpiarRut(rut);
    // Se asume que el último carácter es el dígito verificador.
    std::string numero = rutLimpio.substr(0, rutLimpio.size() - 1);

    // Convertir la cadena numérica a long.
    long parteNumerica = std::stol(numero);
    return parteNumerica;
}