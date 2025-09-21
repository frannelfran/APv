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

  while (!cadena.empty()) {
    char simbolo = cadena[0];
    bool transicionEncontrada = false;

    // Recorro las transiciones del estado actual
    set<Transicion> transiciones = estadoActual_->getTransiciones();
    for (const Transicion& transicion : transiciones) {
      // Si la transicion coincide con el símbolo de entrada y el símbolo en la cima de la pila
      if (transicion.getLecturaCadena() == simbolo && (transicion.getLecturaPila() == '.' || (!pila_.empty() && transicion.getLecturaPila() == pila_.top()))) {
        // Ejecuto la transición
        estadoActual_ = transicion.ejecutar(pila_);
        transicionEncontrada = true;
        break;
      }
    }

    if (!transicionEncontrada) {
      throw runtime_error("Error: No se encontró una transición válida.");
    }

    // Avanzo en la cadena de entrada
    cadena.erase(0, 1);
  }

  // Al finalizar la cadena, verifico si la pila está vacía
  if (!pila_.empty()) {
    cout << "La cadena no pertenece al lenguaje" << endl;
  } else {
    cout << "La cadena pertenece al lenguaje" << endl;
  }
}

/**
 * @brief Método para reiniciar el autómata a su estado inicial
 * @return void
 */
void Automata::reiniciar() {
  // Reinicio la pila
  while (!pila_.empty()) {
    pila_.pop();
  }

  // Apilo el símbolo inicial de la pila
  for (char simbolo : topPila_) {
    pila_.push(simbolo);
  }

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