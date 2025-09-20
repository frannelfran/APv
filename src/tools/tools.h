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
  Alfabeto alfabetoAutomata;
  Alfabeto alfabetoPila;
  set<Estado*> estados;
  Estado* estado_inicial;
  string topPila;
};

Tools leerFichero(const string& nombreFichero);
void leerEstados(istringstream& is);

#endif // TOOLS_H