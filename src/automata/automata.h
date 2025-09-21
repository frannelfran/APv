#pragma once
#include "../alfabeto/alfabeto.h"
#include "../transicion/transicion.h"
#include "../estado/estado.h"
#include <stack> // Para la pila

#ifndef AUTOMATA_H
#define AUTOMATA_H

/**
 * @class Automata
 * @brief Clase que representa un autómata
 */
class Automata {
  public:
    // Constructor y destructor
    Automata(const set<Estado*>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoPila, const string& topPila);
    ~Automata() = default;

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Automata& automata);

    // Métodos
    void ejecutar(string cadena);
    bool esValida(const string& cadena) const;
    void reiniciar();

  private:
    set<Estado*> estados_;
    Alfabeto alfabetoEntrada_;
    Alfabeto alfabetoPila_;
    stack<char> pila_;
    string topPila_;
    Estado* estadoActual_;
};

#endif // AUTOMATA_H