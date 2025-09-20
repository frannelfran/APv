#include "estado.h"
#include "../transicion/transicion.h" // Ahora sí podemos incluir la definición completa

/**
 * @brief Agrega una transición al estado
 * @param transicion La transición a agregar
 */
void Estado::agregarTransicion(const Transicion& transicion) {
  transiciones_.insert(transicion);
}