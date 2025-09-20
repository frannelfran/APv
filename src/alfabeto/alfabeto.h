#pragma once
#include <iostream>
#include <set>

#ifndef ALFABETO_H
#define ALFABETO_H

using namespace std;

/**
 * @class Alfabeto
 * @brief Clase que representa un alfabeto de símbolos
 */
class Alfabeto {
  public:
    // Constructor y destructor
    Alfabeto() = default;
    ~Alfabeto() = default;

    // Métodos
    inline void insertar(char simbolo) { simbolos_.insert(simbolo); }
    inline bool pertenece(char simbolo) const { return simbolos_.find(simbolo) != simbolos_.end(); }
    inline size_t size() const { return simbolos_.size(); }

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Alfabeto& alfabeto);

  private:
    set<char> simbolos_;
};

#endif // ALFABETO_H