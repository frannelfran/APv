# APv
Para esta práctica yo he decidio representar un autómata por **vaciado de pila (APv)**.
## Estructura de directorios
```
.
├── data
│   ├── APv-1.txt
│   ├── APv-2.txt
│   └── APv-3.txt
├── makefile
├── README.md
└── src
    ├── alfabeto
    │   ├── alfabeto.cc
    │   └── alfabeto.h
    ├── automata
    │   ├── automata.cc
    │   └── automata.h
    ├── estado
    │   ├── estado.cc
    │   └── estado.h
    ├── main.cc
    ├── tools
    │   ├── tools.cc
    │   └── tools.h
    └── transicion
        ├── transicion.cc
        └── transicion.h
```
## Estructura del programa
### Clase Alfabeto
Esta clase sirve para represntar tanto el alfabeto de entrada como el alfabeto de la cinta. Tiene los siguientes métodos.
#### Métodos principales

```cpp
// Constructor y destructor
Alfabeto() = default;
~Alfabeto() = default;

// Métodos
inline void insertar(char simbolo) { simbolos_.insert(simbolo); }
inline bool pertenece(char simbolo) const { return simbolos_.find(simbolo) != simbolos_.end(); }
inline size_t size() const { return simbolos_.size(); }

// Sobrecarga de operadores
friend ostream& operator<<(ostream& os, const Alfabeto& alfabeto);
```
- **insertar(char simbolo):** Inserta un símbolo en el alfabeto.
- **pertenece(char simbolo):** Comprueba si un símbolo pertenece al alfabeto.
- **size():** Devuelve el número de símbolos en el alfabeto.
- **operator<<:** Permite mostrar el alfabeto por pantalla de forma sencilla.

### Clase Transicion
Esta clase representa una transición del autómata de pila. Cada transición define cómo el autómata cambia de estado, qué lee de la cadena de entrada, qué lee/escribe en la pila.

#### Métodos principales

```cpp
// Constructor
Transicion(const int& id, const char& lecturaCadena, const char& lecturaPila, 
          Estado* actual, Estado* siguiente, const string& apilar);

// Getters
inline char getLecturaCadena() const { return lecturaCadena_; }
inline char getLecturaPila() const { return lecturaPila_; }
inline int getId() const { return id_; }

// Métodos
Estado* ejecutar(stack<char>& pila, string& cadena);

// Sobrecarga de operadores
friend ostream& operator<<(ostream& os, const Transicion& transicion);
```
- **Constructor:** Inicializa una transición con su ID, símbolos de lectura, estados y símbolos a apilar.
- **getLecturaCadena():** Devuelve el símbolo que se lee de la cadena de entrada.
- **getLecturaPila():** Devuelve el símbolo que se lee de la cima de la pila.
- **getId():** Devuelve el identificador único de la transición.
- **ejecutar():** Ejecuta la transición, modificando la pila y la cadena según corresponda.
- **operator<<:** Permite mostrar la transición en formato legible.

### Clase Estado
Esta clase representa un estado del autómata. Cada estado puede tener múltiples transiciones y puede ser marcado como estado inicial.

#### Métodos principales

```cpp
// Constructor
Estado(const string& id, const bool& inicial = false);

// Getters
inline string getId() const { return id_; }
inline bool esInicial() const { return inicial_; }
inline vector<Transicion>& getTransiciones() { return transiciones_; }

// Setters
inline void setInicial() { inicial_ = true; }

// Métodos
void agregarTransicion(const Transicion& transicion);

// Sobrecarga de operadores
friend ostream& operator<<(ostream& os, const Estado& estado);
```
- **Constructor:** Crea un estado con un identificador y opcionalmente lo marca como inicial.
- **getId():** Devuelve el identificador del estado.
- **esInicial():** Indica si el estado es el estado inicial del autómata.
- **getTransiciones():** Devuelve las transiciones disponibles desde este estado.
- **setInicial():** Marca el estado como inicial.
- **agregarTransicion():** Añade una nueva transición al estado.
- **operator<<:** Permite mostrar el estado y sus transiciones.

### Clase Automata
Esta es la clase principal que representa el autómata de pila por vaciado. Coordina todos los componentes y ejecuta el procesamiento de cadenas.

#### Métodos principales

```cpp
// Constructor
Automata(const set<Estado*>& estados, const Alfabeto& alfabetoEntrada, 
         const Alfabeto& alfabetoPila, const string& topPila);

// Métodos principales
bool ejecutar(string cadena);
bool esValida(const string& cadena) const;
void reiniciar();
void resetearPila();
void mostrarTraza(const string& cadena, const vector<Transicion*>& transiciones);
vector<Transicion*> obtenerTransicionesPosibles(char simbolo, vector<Transicion*> transicionesUsadas);

// Sobrecarga de operadores
friend ostream& operator<<(ostream& os, const Automata& automata);
```
- **Constructor:** Inicializa el autómata con sus estados, alfabetos y símbolo inicial de pila.
- **ejecutar():** Procesa una cadena de entrada y devuelve si es aceptada por el autómata.
- **esValida():** Verifica si una cadena contiene solo símbolos del alfabeto de entrada.
- **reiniciar():** Restaura el autómata a su estado inicial.
- **resetearPila():** Reinicia la pila al estado inicial.
- **mostrarTraza():** Muestra el estado actual del autómata durante la ejecución.
- **obtenerTransicionesPosibles():** Devuelve las transiciones aplicables en el estado actual.
- **operator<<:** Permite mostrar la configuración completa del autómata.
## Compilación del programa
Para compilar este programa he creado un archivo `makefile` para automatizar el trabajo, solo basta con ejecutar lo siguiente:
```bash
make
```
Para borrar el ejecutable generado basta con ejecutar lo siguiente:
```bash
make clean
```
## Ejecución del programa
Para que este programa pueda rrealizar su correcto funcionamiento se le debe pasar un fichero en formato `.txt` con los datos del autómata, el fichero tendra la siguiente estructura:
```txt
# Comentarios
q1 q2 q3 … # conjunto Q
a1 a2 a3 … # conjunto Σ(*1)
A1 A2 A3 … # conjunto Γ(*1)
q1 # estado inicial
A1 # símbolo inicial de la pila
# función de transición: (q2, A) ∈ δ (q1, a, A1)
q1 a^(*2) A1 q2 A^(*3)
... # cada una de las transiciones en una línea distinta

(*1) Los símbolos contenidos en Σ y en Γ estarán formados por un único carácter.
(*2) a es un símbolo de (Σ ⋃ ε). En el fichero el símbolo ε se representará por un
punto (.)
(*3) A puede ser ε (que se escribirá también en el fichero mediante un punto) o
estar formado por uno o más símbolos de Γ, que se escribirán sin espacios en
blanco. Por ejemplo: A = A1A1A1
```



