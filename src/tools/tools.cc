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

  // Leo el alfabeto de entrada
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
  comprobarSimboloPila(linea[0]);
  datos.topPila = linea;

  // Leo las transiciones
  int id = 1;
  while (getline(file, linea)) {
    if (linea.empty() || linea[0] == '#') {
      continue;
    }
    leerTransiciones(istringstream(linea), id++);
  }
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
 * @param id Identificador de la transición
 * @return void
 */
void leerTransiciones(istringstream is, int id) {
  string actual, simbolo_entrada, simboloPila, siguiente, topPila;
  is >> actual >> simbolo_entrada >> simboloPila >> siguiente >> topPila;
  // Compruebo los estados
  comprobarEstado(actual), comprobarEstado(siguiente);
  // Compruebo los símbolos
  comprobarSimboloEntrada(simbolo_entrada[0]);
  comprobarSimboloPila(simboloPila[0]);
  comprobarSimboloPila(topPila[0]);
  // Busco el estaddo inicial y siguiente en el conjunto de estados
  Estado* estadoSiguiente = buscarEstado(siguiente), *estadoActual = buscarEstado(actual);
  // Creo la transición y la agrego la transicion
  Transicion transicion(id, simbolo_entrada[0], simboloPila[0], estadoActual, estadoSiguiente, topPila);
  for (Estado* e : datos.estados) {
    if (e->getId() == actual) {
      e->agregarTransicion(transicion);
      break;
    }
  }
}

/**
 * @brief Método para buscar un estado en el conjunto de estados
 * @param estado Estado a buscar
 * @return Puntero al estado si se encuentra, nullptr en caso contrario
 */
Estado* buscarEstado(const string& estado) {
  for (Estado* e : datos.estados) {
    if (e->getId() == estado) {
      return e;
    }
  }
  return nullptr;
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
    cerr << "Q -> {";
    for (auto it = datos.estados.begin(); it != datos.estados.end(); ++it) {
      cerr << (*it)->getId();
      if (next(it) != datos.estados.end()) {
        cerr << ", ";
      }
    }
    cerr << "}" << endl;
    throw runtime_error("El estado " + estado + " no está en el conjunto de estados.");
  }
}

/**
 * @brief Comprueba que un símbolo pertenece al alfabeto de entrada (Σ)
 */
void comprobarSimboloEntrada(const char& simbolo) {
  if (simbolo == '.') return; // epsilon siempre permitido en lectura de cadena
  if (!datos.alfabetos.first.pertenece(simbolo)) {
    cerr << "Σ -> " << datos.alfabetos.first << endl;
    throw runtime_error(string("El símbolo '") + simbolo + "' no pertenece al alfabeto de entrada (Σ).");
  }
}

/**
 * @brief Comprueba que un símbolo pertenece al alfabeto de la pila (Γ)
 */
void comprobarSimboloPila(const char& simbolo) {
  if (simbolo == '.') return; // epsilon siempre permitido en lectura/escritura de pila
  if (!datos.alfabetos.second.pertenece(simbolo)) {
    cerr << "Γ -> " << datos.alfabetos.second << endl;
    throw runtime_error(string("El símbolo '") + simbolo + "' no pertenece al alfabeto de la pila (Γ).");
  }
}

/**
 * @brief Función para mostrar la cabecera de la traza
 * @return void
 */
void mostrarCabecera() {
  cout << "------------------------------------------------------------" << endl;
  cout << left;
  cout << setw(15) << "Estado actual" 
  << setw(15) << "Cadena" 
  << setw(15) << "Pila" 
  << setw(15) << "Transiciones" << endl;
  cout << "------------------------------------------------------------" << endl;
}
