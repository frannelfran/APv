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
Transicion::Transicion(const int& id, const char& lecturaCadena, const char& lecturaPila, Estado* siguiente, const string& apilar) {
  id_ = id;
  lecturaCadena_ = lecturaCadena;
  lecturaPila_ = lecturaPila;
  siguiente_ = siguiente;
  apilar_ = apilar;
}

/**
 * @overload Sobrecarga del operador de salida para imprimir una transición
 */
ostream& operator<<(ostream& os, const Transicion& transicion) {
  os << ", " << transicion.lecturaCadena_ << ", " << transicion.lecturaPila_ << ") -> (" 
     << transicion.siguiente_->getId() << ", " << transicion.apilar_ << ") " << transicion.id_;
  return os;
}