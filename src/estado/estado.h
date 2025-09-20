#pragma once
#include <iostream>
#include <set>

#ifndef ESTADO_H
#define ESTADO_H

using namespace std;

// Forward declaration para evitar dependencia circular
class Transicion;

/**
 * @class Estado
 * @brief Clase que representa un estado en un autómata
 */
class Estado {
  public:
    // Constructor y destructor
    Estado() = default;
    Estado(const string& id, const bool& inicial = false) : id_(id), inicial_(inicial) {}

    // Getters
    inline string getId() const { return id_; }
    inline bool esInicial() const { return inicial_; }

  private:
    string id_;
    set<Transicion> transiciones_;
    bool inicial_;
};

#endif // ESTADO_H