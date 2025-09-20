#include "tools/tools.h"
#include <iostream>

using namespace std;

/**
 * @brief Función principal del programa
 * @param argc Número de argumentos
 * @param argv Vector de argumentos
 * @return Código de salida
 */

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Uso: " << argv[0] << " <fichero_entrada>" << endl;
    return 1;
  }

  try {
    string nombreFichero = argv[1];
    Tools datos = leerFichero(nombreFichero);
    cout << "Fichero leído correctamente." << endl;

    for (const Estado* estado : datos.estados) {
      cout << *estado << endl;
    }

    // Aquí se puede continuar con la lógica del autómata utilizando los datos leídos
    return 0;
  } catch (const exception& e) {
    cerr << "Error: " << e.what() << endl;
    return 1;
  }
}