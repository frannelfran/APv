#include "automata.h"

/**
 * @brief Constructor de la clase Automata
 * @param estados Conjunto de estados del autómata
 * @param alfabetoEntrada Alfabeto de entrada del autómata
 * @param alfabetoPila Alfabeto de la pila del autómata
 * @param topPila Símbolo inicial de la pila
 */
Automata::Automata(const set<Estado*>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoPila, const string& topPila) {
  estados_ = estados;
  alfabetoEntrada_ = alfabetoEntrada;
  alfabetoPila_ = alfabetoPila;
  topPila_ = topPila;
 for (char simbolo : topPila_) {
    pila_.push(simbolo);
  }

  // Inicializo el estado actual al estado inicial
  for (Estado* estado : estados_) {
    if (estado->esInicial()) {
      estadoActual_ = estado;
      break;
    }
  }
}

/**
 * @brief Método para ejecutar el autómata con una cadena de entrada
 * @param cadena Cadena de entrada
 * @return void
 */
void Automata::ejecutar(string cadena) {
  if (!esValida(cadena)) {
    throw runtime_error("Error: La cadena contiene símbolos que no pertenecen al alfabeto de entrada.");
  }
  
  string cadenaOriginal = cadena;
  reiniciar(); // Asegurar que empezamos desde el estado inicial
  
  // Utilizamos un enfoque recursivo con backtracking
  bool aceptada = ejecutarRecursivo(cadena, cadenaOriginal);
  
  mostrarTraza(cadena, vector<Transicion*>());
  
  if (aceptada) {
    cout << "La cadena pertenece al lenguaje" << endl;
  } else {
    cout << "La cadena no pertenece al lenguaje" << endl;
  }
}


/**
 * @brief Método auxiliar recursivo para la ejecución del autómata con backtracking
 * @param cadena Cadena de entrada (por referencia para modificar)
 * @param cadenaOriginal Cadena original para mostrar en la traza
 * @return true si la cadena es aceptada, false en caso contrario
 */
bool Automata::ejecutarRecursivo(string& cadena, const string& cadenaOriginal) {
  vector<Transicion*> transicionesPosibles = obtenerTransicionesPosibles(cadena, vector<Transicion*>());
  
  mostrarTraza(cadena, transicionesPosibles);
  
  // Caso base: si la cadena está vacía y la pila está vacía, aceptamos
  if (cadena.empty() && pila_.empty()) {
    return true;
  }
  
  // Si no hay transiciones posibles, rechazamos
  if (transicionesPosibles.empty()) {
    return false;
  }
  
  // Probamos cada transición posible
  for (Transicion* transicion : transicionesPosibles) {
    // Guardamos el estado actual
    Estado* estadoAnterior = estadoActual_;
    stack<char> pilaAnterior = pila_;
    string cadenaAnterior = cadena;
    
    try {
      // Ejecutamos la transición
      estadoActual_ = transicion->ejecutar(pila_, cadena);
      
      // Llamada recursiva
      if (ejecutarRecursivo(cadena, cadenaOriginal)) {
        return true; // Encontramos un camino exitoso
      }
      
      // Backtracking: restauramos el estado
      estadoActual_ = estadoAnterior;
      pila_ = pilaAnterior;
      cadena = cadenaAnterior;
      
    } catch (const runtime_error& e) {
      // Si hay error en la ejecución de la transición, continuamos con la siguiente
      estadoActual_ = estadoAnterior;
      pila_ = pilaAnterior;
      cadena = cadenaAnterior;
      continue;
    }
  }
  
  return false; // No se encontró camino exitoso
}


/**
 * @brief Método para obtener las transiciones posibles desde el estado actual
 * @param cadena Cadena de entrada
 * @param transicionesUsadas Vector de transiciones usadas (no utilizado en la nueva implementación)
 * @return Vector de transiciones posibles
 */
vector<Transicion*> Automata::obtenerTransicionesPosibles(string cadena, vector<Transicion*> transicionesUsadas) {
  vector<Transicion*> transicionesPosibles;
  char simbolo = cadena.empty() ? '.' : cadena[0];
  char topePila = pila_.empty() ? '.' : pila_.top();
  
  for (auto& transicion : estadoActual_->getTransiciones()) {
    // Verificar si la transición es aplicable
    bool simboloCorrecto = (transicion.getLecturaCadena() == simbolo || transicion.getLecturaCadena() == '.');
    bool pilaCorrecto = (transicion.getLecturaPila() == topePila || transicion.getLecturaPila() == '.');
    
    if (simboloCorrecto && pilaCorrecto) {
      transicionesPosibles.push_back(&transicion);
    }
  }
  
  return transicionesPosibles;
}

/**
 * @brief Método para mostrar la traza de la ejecución del autómata
 * @param cadena Cadena de entrada
 * @param transiciones Vector de transiciones disponibles
 * @return void
 */
void Automata::mostrarTraza(const string& cadena, const vector<Transicion*>& transiciones) {
  // Mostrar el contenido de la pila
  string pilaStr;
  stack<char> pilaCopia = pila_;
  while (!pilaCopia.empty()) {
    pilaStr = pilaCopia.top() + pilaStr;
    pilaCopia.pop();
  }

  reverse(pilaStr.begin(), pilaStr.end());

  cout << left
  << setw(15) << estadoActual_->getId()
  << setw(15) << (cadena.empty() ? "." : cadena)
  << setw(15) << (pilaStr.empty() ? "-" : pilaStr);

  if (transiciones.empty()) {
    cout << setw(15) << "-";
    cout << "\n------------------------------------------------------------" << endl;
    return;
  }
  
  // Mostrar las transiciones posibles
  for (auto it = transiciones.begin(); it != transiciones.end(); ++it) {
    cout << left
    << setw(0) << (*it)->getId();
    if (next(it) != transiciones.end()) {
      cout << ", ";
    }
  }
  cout << "\n------------------------------------------------------------" << endl;
}

/**
 * @brief Método para restablecer la pila al estado inicial
 * @return void
 */
void Automata::resetearPila() {
  while (!pila_.empty()) {
    pila_.pop();
  }
  // Apilo el símbolo inicial de la pila
  for (char simbolo : topPila_) {
    pila_.push(simbolo);
  }
}

/**
 * @brief Método para reiniciar el autómata a su estado inicial
 * @return void
 */
void Automata::reiniciar() {
  // Reinicio la pila
  resetearPila();

  // Reinicio el estado actual al estado inicial
  for (Estado* estado : estados_) {
    if (estado->esInicial()) {
      estadoActual_ = estado;
      break;
    }
  }
}

/**
 * @brief Método para comprobar si una cadena es válida para el autómata
 * @param cadena Cadena de entrada
 * @return true si la cadena es válida, false en caso contrario
 */
bool Automata::esValida(const string& cadena) const {
  for (char simbolo : cadena) {
    if (!alfabetoEntrada_.pertenece(simbolo)) {
      return false;
    }
  }
  return true;
}

/**
 * @overload Sobrecarga del operador << para mostrar el autómata
 */
ostream& operator<<(ostream& os, const Automata& automata) {
  os << "Q -> {";
  for (auto it = automata.estados_.begin(); it != automata.estados_.end(); ++it) {
    os << (*it)->getId();
    if (next(it) != automata.estados_.end()) {
      os << ", ";
    }
  }
  os << "}" << endl;
  os << "Σ -> " << automata.alfabetoEntrada_ << endl;
  os << "Γ -> " << automata.alfabetoPila_ << endl;
  os << "q0 -> " << automata.estadoActual_->getId() << endl;
  os << "Z0 -> " << automata.pila_.top() << endl;
  
  for (Estado* estado : automata.estados_) {
    os << *estado << endl;
  }
  return os;
}