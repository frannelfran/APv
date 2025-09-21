#include "transicion.h"
#include "../estado/estado.h"

/**
 * @brief Constructor de la clase Transicion
 * @param id Identificador de la transición
 * @param lecturaCadena Símbolo que se lee de la cadena de entrada
 * @param lecturaPila Símbolo que se lee de la pila
 * @param siguiente Puntero al estado siguiente
 * @param apilar Cadena de símbolos a apilar en la pila
 */
Transicion::Transicion(const int& id, const char& lecturaCadena, const char& lecturaPila, Estado* actual, Estado* siguiente, const string& apilar) {
  id_ = id;
  lecturaCadena_ = lecturaCadena;
  lecturaPila_ = lecturaPila;
  siguiente_ = siguiente;
  actual_ = actual; 
  apilar_ = apilar;
  usada_ = false;
}

/**
 * @brief Ejecuta la transicion, modificando lo que hay en la pila
 * @param pila Pila del autómata
 * @param cadena Cadena de entrada
 * @return Estado siguiente al que se transita
 */
Estado* Transicion::ejecutar(stack<char>& pila, string& cadena) {
  // Si el símbolo a leer de la pila es diferente de epsilon
  if (lecturaPila_ != '.') {
    // Si la pila está vacía, no se puede leer
    if (pila.empty()) {
      throw runtime_error("La pila está vacía, no se puede leer el símbolo '" + string(1, lecturaPila_) + "'.");
    } else if (pila.top() != lecturaPila_) { // Si no coincide el símbolo en la cima de la pila
      throw runtime_error("Error: El símbolo en la cima de la pila es '" + string(1, pila.top()) + "', pero se esperaba '" + string(1, lecturaPila_) + "'.");
    }
    // Si coincide, desapilamos
    pila.pop();
  }

  // Apilamos los símbolos indicados en apilar_ (si no es epsilon)
  if (apilar_ != ".") {
    for (auto it = apilar_.rbegin(); it != apilar_.rend(); ++it) {
      pila.push(*it);
    }
    cadena.erase(0, 1);
  }
  return siguiente_;
}

/**
 * @overload Sobrecarga del operador de salida para imprimir una transición
 */
ostream& operator<<(ostream& os, const Transicion& transicion) {
  os << "(" << transicion.actual_->getId() << ", " << transicion.lecturaCadena_ << ", " << transicion.lecturaPila_ << ") -> (" 
     << transicion.siguiente_->getId() << ", " << transicion.apilar_ << ") " << transicion.id_;
  return os;
}