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
  leerEstados(istringstream(linea));

  // Leo el alfabeto del autómata
  getline(file, linea);
  leerAlfabeto(istringstream(linea));

  // Leo el alfabeto de la pila
  getline(file, linea);
  leerAlfabeto(istringstream(linea));

  // Leo el estado inicial
  getline(file, linea);
  string estado_inicial_id = linea;
  for (Estado* estado : datos.estados) {
    if (estado->getId() == estado_inicial_id) {
      estado->setInicial();
      break;
    }
    else {
      throw runtime_error("El estado inicial " + estado_inicial_id + " no está en el conjunto de estados.");
    }
  }

  // Leo el símbolo inicial de la pila
  getline(file, linea);
  if (datos.alfabetos.second.pertenece(linea[0])) {
    datos.topPila = linea;
  } else {
    throw runtime_error("El símbolo inicial de la pila " + linea + " no pertenece al alfabeto de la pila.");
  }

  // Leo las transiciones
  leerTransiciones(istringstream(linea));
  return datos;
}

/**
 * @brief Función para leer el conjunto de estados
 * @param is Stream de entrada
 * @return void
 */
void leerEstados(istringstream is) {
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

/**
 * @brief Función para leer las transiciones del fichero
 * @param is Stream de entrada
 * @return void
 */
void leerTransiciones(istringstream is) {
  string linea;
  while (is >> linea) {
    
  }
}