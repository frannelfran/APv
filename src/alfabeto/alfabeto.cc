#include "alfabeto.h"

/**
 * @overload Sobrecarga del operador de salida pàra mostrar el alfabeto
 */
ostream& operator<<(ostream& os, const Alfabeto& alfabeto) {
  os << "{ ";
  for (const char& simbolo : alfabeto.simbolos_) {
    os << simbolo << " ";
  }
  os << "}";
  return os;
}