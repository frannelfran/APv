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
  comprobarEstado(linea);
  for (Estado* estado : datos.estados) {
    if (estado->getId() == linea) {
      estado->setInicial();
      break;
    }
  }

  // Leo el símbolo inicial de la pila
  getline(file, linea);
  comprobarSimbolo(linea[0]);
  datos.topPila = linea;

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
  int id = 1;
  while (is >> linea) {
    string actual, simbolo_entrada, simbolo_pila, siguiente, nuevo_simbolo_pila;
    is >> actual >> simbolo_entrada >> simbolo_pila >> siguiente >> nuevo_simbolo_pila;
    
    // Compruebo los estados
    comprobarEstado(actual), comprobarEstado(siguiente);
    // Compruebo los símbolos
    


  }
}

/**
 * @brief Función para combrobar que los estados pertencen al conjunto de estados
 * @param actual Estado actual
 * @param siguiente Estado siguiente
 * @return void
 */
void comprobarEstado(const string& estado) {
  bool encontrado = false;
  for (Estado* e : datos.estados) {
    if (e->getId() == estado) {
      encontrado = true;
    }
  }

  if (!encontrado) {
    throw runtime_error("El estado " + estado + " no está en el conjunto de estados.");
  }
}

/**
 * @brief Función para comprobar que el símbolo pertenece al alfabeto del autómata
 * @param simbolo Símbolo a comprobar
 * @return void
 */
void comprobarSimbolo(const char& simbolo) {
  bool simboloAutomata = false, simboloPila = false;

  if (simbolo == '.') { // epsilon siempre pertenece
    return;
  } else if (datos.alfabetos.first.pertenece(simbolo)) {
    simboloAutomata = true;
  } else if (datos.alfabetos.second.pertenece(simbolo)) {
    simboloPila = true;
  }

  if (!simboloAutomata) {
    throw runtime_error("El símbolo de entrada " + string(1, simbolo) + " no pertenece al alfabeto del autómata.");
  } else if (!simboloPila) {
    throw runtime_error("El símbolo de la pila " + string(1, simbolo) + " no pertenece al alfabeto de la pila.");
  }
}