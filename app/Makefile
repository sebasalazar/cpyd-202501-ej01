CXX = g++
CXXFLAGS = -g3 -Wall -std=c++17
MKDIR = mkdir -p

LIBS = -lm

directorios:
	$(MKDIR) build dist

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

Utilidades.o: directorios Utilidades.cpp
	$(CXX) $(CXXFLAGS) -c Utilidades.cpp -o build/Utilidades.o

Persona.o: directorios Persona.cpp
	$(CXX) $(CXXFLAGS) -c Persona.cpp -o build/Persona.o

all: clean main.o Persona.o Utilidades.o
	$(CXX) $(CXXFLAGS) -o dist/programa \
	build/main.o \
        build/Persona.o \
	build/Utilidades.o \
	$(LIBS)
	rm -fr build

clean:
	rm -fr *.o a.out core programa dist build

.DEFAULT_GOAL := all
