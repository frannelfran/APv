#pragma once
#include <iostream>
#include <set>
#include "../transicion/transicion.h"

#ifndef ESTADO_H
#define ESTADO_H

using namespace std;

/**
 * @class Estado
 * @brief Clase que representa un estado en un autómata
 */
class Estado {
  public:
    // Constructor y destructor
    Estado() = default;
    Estado(const string& id, set<Transicion> transiciones, const bool& inicial = false) : id_(id), transiciones_(transiciones) {}

  private:
    string id_;
    set<Transicion> transiciones_;
    bool inicial_;
};

#endif // ESTADO_H