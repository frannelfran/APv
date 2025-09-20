# Compilador y flags
CXX := g++
CXXFLAGS := -std=c++20 -I include -O0 -g

# Obtener todos los archivos .cc en el proyecto (recursivamente)
SRCS := $(shell find . -name '*.cc')

# Nombre del ejecutable
TARGET := apv

.PHONY: all clean

all: $(TARGET)

# Compilar todos los .cc directamente en el ejecutable
$(TARGET): $(SRCS)
	@echo "Compilando y enlazando..."  
	$(CXX) $(CXXFLAGS) $^ -o $@       

clean:
	@echo "Eliminando ejecutable..."  
	rm -f $(TARGET)                   