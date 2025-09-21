#include "estado.h"
#include "../transicion/transicion.h" // Ahora sí podemos incluir la definición completa

/**
 * @brief Agrega una transición al estado
 * @param transicion La transición a agregar
 */
void Estado::agregarTransicion(const Transicion& transicion) {
  transiciones_.insert(transicion);
}

/**
 * @overload Sobrecarga del operador <<
 */
ostream& operator<<(ostream& os, const Estado& estado) {
  os << "---- Transiciones del estado " << estado.id_ << " ----" << endl;
  for (auto it = estado.transiciones_.begin(); it != estado.transiciones_.end(); ++it) {
    os << *it << endl;
  }
  return os;
}