#pragma once
#include "../alfabeto/alfabeto.h"
#include "../estado/estado.h"
#include "../transicion/transicion.h"
#include <fstream> // Para manejo de archivos
#include <stdexcept> // Para las excepciones
#include <sstream> // Para istringstream

#ifndef TOOLS_H
#define TOOLS_H

/**
 * @struct Tools
 * @brief Estructura para almacenar los datos del fichero de entrada
 */
struct Tools {
  pair<Alfabeto, Alfabeto> alfabetos;
  set<Estado*> estados;
  string topPila;
};

Tools leerFichero(const string& nombreFichero);
void leerEstados(istringstream is);
void leerAlfabeto(istringstream is);
void leerTransiciones(istringstream is);
void comprobarEstado(const string& estado);
void comprobarSimbolo(const char& simbolo);

#endif // TOOLS_H