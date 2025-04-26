#include <iostream>
#include <fstream>
#include <string>
#include <future>
#include <vector>
#include "Utilidades.h"
#include "Persona.h"
#include "ServicioBD.h"
#include "Opcional.h"



/**
 * Función que muestra los participantes del grupo
 * @param programa nombre del ejecutable
 */
void participantes(std::string programa);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */
int main(int argc, char** argv) {
    if (argc > 1) {
        std::string nombreArchivo = std::string(argv[1]);

        std::vector<Persona> personas;
        std::ifstream archivo(nombreArchivo);
        if (archivo) {
            std::string linea;
            // Se itera línea por línea del archivo
            while (std::getline(archivo, linea)) {
                if (linea.empty())
                    continue; // Se omiten las líneas vacías

                std::vector<std::string> tokens;
                std::istringstream ss(linea);
                std::string token;

                // Se utiliza ';' como delimitador para obtener cada token
                while (std::getline(ss, token, ';')) {
                    // Se remueven las comillas del inicio y final del token
                    if (token.size() >= 2 && token.front() == '\"' && token.back() == '\"') {
                        token = token.substr(1, token.size() - 2);
                    }
                    tokens.push_back(token);
                }

                // Se comprueba que la línea tenga exactamente 4 campos
                if (tokens.size() == 4) {
                    // Se crea el objeto Persona usando el constructor que espera:
                    // 1. RUT (como cadena) que luego se convierte internamente,
                    // 2. Nombres,
                    // 3. Apellidos,
                    // 4. Fecha de nacimiento (en formato "YYYY-MM-DD")
                    Persona p(tokens[0], tokens[1], tokens[2], tokens[3]);
                    personas.push_back(p);
                } else {
                    std::cerr << "Advertencia: Línea con formato incorrecto -> " << linea << "\n";
                }
            }

            // En este punto, almaceno los datos en la base de datos
            ServicioBD db;
            for (Persona& p : personas) {
                Opcional<Persona> original = db.getPersonaByRut(p.GetRut());
                if (original.estaPresente()) {
                    db.updatePersona(p.GetRut(), p.GetNombres(), p.GetApellidos(), p.GetFechaNacimiento());
                } else {
                    db.createPersona(p.GetRut(), p.GetNombres(), p.GetApellidos(), p.GetFechaNacimiento());
                }
            }
        }
        archivo.close();
    } else {
        // Mostrar los integrantes
        participantes(argv[0]);
    }
    return 0;
}

void participantes(std::string programa) {
    std::cout << std::endl << "=== Taller " << programa << " ===" << std::endl;
    std::cout << std::endl << "Sebastián Salazar Molina" << std::endl; // Reemplazar por su nombre
}
