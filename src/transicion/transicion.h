#pragma once
#include <string>
#include <stack> // Para la pila

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
    Transicion(const int& id, const char& lecturaCadena, const char& lecturaPila, Estado* actual, Estado* siguiente, const string& apilar);
    ~Transicion() = default;

    // Getters
    inline char getLecturaCadena() const { return lecturaCadena_; }
    inline char getLecturaPila() const { return lecturaPila_; }
    inline int getId() const { return id_; }
    inline bool getUsada() const { return usada_; }
    inline Estado* getActual() const { return actual_; }
    stack<char> getPila() const { return pila_; }

    // Setters
    inline void setUsada() { usada_ = true; }
    inline void setCadena(const string& cadena) { cadena_ = cadena; }
    inline void setPila(const stack<char>& pila) { pila_ = pila; }

    // Métodos
    Estado* ejecutar(stack<char>& pila, string& cadena);

    // Sobrecarga de operadores
    inline bool operator==(const Transicion& other) const { return id_ == other.id_; }
    friend ostream& operator<<(ostream& os, const Transicion& transicion);

  private:
    int id_;
    char lecturaCadena_;
    char lecturaPila_;
    Estado* actual_;
    Estado* siguiente_;
    string apilar_;
    bool usada_;
    stack<char> pila_; // Pila asociada a la transición
    string cadena_; // Cadena asociada a la transición
};

#endif // TRANSICION_H