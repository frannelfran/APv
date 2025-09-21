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

  vector<pair<string, Transicion>> transiciones;

  while (!cadena.empty()) {
    char simbolo = cadena[0];
    bool transicionEncontrada = false;

    // Recorro las transiciones del estado actual
    transiciones = obtenerTransicionesPosibles(cadena);
    mostrarTraza(cadena, transiciones);
    pair<string, Transicion> elegida;
    // Miro en el vector de transiciones cual es la que no se ha usado para la cadena en la iteracion
    for (auto it : transiciones) {
      if (!it.second.getUsada()) {
        elegida = it;
        transicionEncontrada = true;
        break;
      }
    }
    if (!transicionEncontrada) {
      throw runtime_error("Error: No se encontró una transición válida.");
    }

    cadena = elegida.first;
    elegida.second.ejecutar(pila_);
    // Avanzo en la cadena de entrada
    cadena.erase(0, 1);

    // Cuento si quedan transiciones sin activar
    int transicionesPosibles = count_if(transiciones.begin(), transiciones.end(), [](const pair<string, Transicion>& p) { return p.second.getUsada() == false; });

    if (cadena.empty() && transicionesPosibles > 0) {
      // Busco aquella transicion que todavía se pueda activar
      for (auto it : transiciones) {
        if (it.second.getUsada() == false) {
          cadena = it.first;
        }
      }
    }
  }
  mostrarTraza(cadena, transiciones);
  // Al finalizar la cadena, verifico si la pila está vacía
  if (!pila_.empty()) {
    cout << "La cadena no pertenece al lenguaje" << endl;
  } else {
    cout << "La cadena pertenece al lenguaje" << endl;
  }
}

/**
 * @brief Método para obtener las transiciones posibles desde el estado actual con un símbolo dado
 * @param cadena Cadena de entrada
 * @return Vector de pares (cadena restante, transición)
 */
vector<pair<string, Transicion>> Automata::obtenerTransicionesPosibles(string cadena) {
  vector<pair<string, Transicion>> transicionesPosibles;
  char simbolo = cadena[0];
  for (const Transicion& transicion : estadoActual_->getTransiciones()) {
    // Verifico si la transición es válida
    if ((transicion.getLecturaCadena() == simbolo || transicion.getLecturaCadena() == '.') &&
        (transicion.getLecturaPila() == (pila_.empty() ? '.' : pila_.top()) || transicion.getLecturaPila() == '.')) {
      // Si la transición es válida, la agrego a las transiciones posibles
      transicionesPosibles.push_back(make_pair(cadena, transicion));
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
void Automata::mostrarTraza(const string& cadena, const vector<pair<string, Transicion>>& transiciones) {
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
  << setw(15) << cadena
  << setw(15) << pilaStr;

  // Mostrar las transiciones posibles
  for (auto it = transiciones.begin(); it != transiciones.end(); ++it) {
    cout << (*it).second.getId();
    if (next(it) != transiciones.end()) {
      cout << ", ";
    }
  }
  cout << "\n------------------------------------------------------------" << endl;
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