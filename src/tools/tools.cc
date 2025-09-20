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
  // Saltar los comentarios y líneas vacías
  while (getline(file, linea)) {
    if (linea.empty() || linea[0] == '#') {
      continue;
    }
    break;
  }
  // Leo los estados
  istringstream iss(linea);
  leerEstados(iss);

  // Leo el alfabeto del autómata
  getline(file, linea);
  leerAlfabeto(istringstream(linea));


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

/**
 * @brief Función para leer los alfabetos del fichero
 * @param is Stream de entrada
 * @return void
 */
void leerAlfabeto(istringstream is) {
  string linea;
  Alfabeto alfabeto;
  while (is >> linea) {
    alfabeto.insertar(linea[0]);
  }
  if (datos.alfabetos.first.size() == 0) {
    datos.alfabetos.first = alfabeto;
  } else {
    datos.alfabetos.second = alfabeto;
  }
}