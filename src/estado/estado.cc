#include "estado.h"
#include "../transicion/transicion.h"

/**
 * @brief Agrega una transición al estado
 * @param transicion La transición a agregar
 */
void Estado::agregarTransicion(const Transicion& transicion) {
  transiciones_.push_back(transicion);
}

/**
 * @overload Sobrecarga del operador <<
 */
ostream& operator<<(ostream& os, const Estado& estado) {
  os << "---- Transiciones del estado " << estado.id_ << " ----" << endl;
  for (auto& it : estado.transiciones_) {
    os << it << endl;
  }
  return os;
}