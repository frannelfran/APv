#include "tools.h"

static Tools datos; // Variable global para almacenar los datos leídos

/**
 * @brief Dunción para leer el fichero de entrada y almacenar los datos en una estructura Tools
 * @param nombreFichero Nombre del fichero de entrada
 * @return Estructura Tools con los datos del fichero
 */
Tools leerFichero(const string& nombreFichero) {
  ifstream file(nombreFichero);

  if (!file.is_open()) { // Comprobar la lectura del fichero
    throw runtime_error("No se pudo abrir el fichero: " + nombreFichero);
  }

  string linea;
  while (getline(file, linea)) {
    // Saltar los comentarios y líneas vacías
    if (linea.empty() || linea[0] == '#') {
      continue;
    }

    set<Estado*> estados;
    // Leo los estados
    istringstream iss(linea);
    leerEstados(iss);


    // Leo el alfabeto
    getline(file, linea);
    set<char> simbolosAutomata;
    for (char simbolo : linea) {
      simbolosAutomata.insert(simbolo);
    }
    datos.alfabetoAutomata = Alfabeto(simbolosAutomata);
    
  }




  return datos;












}

/**
 * @brief Función para leer el conjunto de estados
 * @param is Stream de entrada
 * @return void
 */
void leerEstados(istringstream& is) {
  string linea;
  set<Estado*> estados;
  while (is >> linea) {
    estados.insert(new Estado(linea));
  }
  datos.estados = estados;
}