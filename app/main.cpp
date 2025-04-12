#include <iostream>
#include <string>
#include <cstdlib>


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

    /**
     * Incluir acá la lógica del programa
     * 
     */
    if (argc > 1) {
        // @TODO programar proyecto
    } else {
        // Mostrar los integrantes
        participantes(argv[0]);
    }
    return EXIT_SUCCESS;
}

void participantes(std::string programa) {
    std::cout << std::endl << "=== Taller " << programa << " ===" << std::endl;
    std::cout << std::endl << "Juanito"; // Reemplazar por su nombre
    std::cout << std::endl << "Pedrito"; // Reemplazar por su nombre
    std::cout << std::endl << "Dieguito" << std::endl; // Reemplazar por su nombre
}
