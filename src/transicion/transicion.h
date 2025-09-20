#pragma once
#include <string>

#ifndef TRANSICION_H
#define TRANSICION_H

using namespace std;

// Forward declaration para evitar dependencia circular
class Estado;

/**
 * @class Transicion
 * @brief Clase que representa una transición en un autómata
 */
class Transicion {
  public:
    // Constructor y destructor
    Transicion() = default;
    Transicion(const int& id, const char& lecturaCadena, const char& lecturaPila, Estado* siguiente, const string& apilar);
    ~Transicion() = default;

    // Sobrecarga de operadores
    inline bool operator<(const Transicion& other) const { return id_ < other.id_; }

  private:
    int id_;
    char lecturaCadena_;
    char lecturaPila_;
    Estado* siguiente_;
    string apilar_;
};

#endif // TRANSICION_H