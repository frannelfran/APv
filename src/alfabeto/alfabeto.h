#pragma once
#include <iostream>
#include <set>

#ifndef ALFABETO_H
#define ALFABETO_H

using namespace std;

class Alfabeto {
  public:
    // Constructor y destructor
    Alfabeto() = default;
    Alfabeto(const set<char>& simbolos) : simbolos_(simbolos) {}
    ~Alfabeto() = default;

    // Métodos
    inline bool pertenece(char simbolo) const { return simbolos_.find(simbolo) != simbolos_.end(); }

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Alfabeto& alfabeto);

  private:
    set<char> simbolos_;
};

#endif // ALFABETO_H