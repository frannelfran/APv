#include "estado.h"
#include "../transicion/transicion.h"

/**
 * @brief Constructor de la clase Estado
 * @param id Identificador del estado
 * @param transiciones Conjunto de transiciones del estado
 * @param inicial Indica si es el estado inicial
 */
Estado::Estado(const string& id, const set<Transicion> transiciones, const bool& inicial) {
  id_ = id;
  transiciones_ = transiciones;
  inicial_ = inicial;
}