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

    // Setters
    inline void setInicial() { inicial_ = true; }

    // Métodos
    void agregarTransicion(const Transicion& transicion);

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Estado& estado);
    inline bool operator<(const Estado& other) const { return id_ < other.id_; }

  private:
    string id_;
    set<Transicion> transiciones_; // Volvemos a objetos
    bool inicial_;
};

#endif // ESTADO_H