#ifndef BLOQUES
#define BLOQUES

#include "../Archivo.h"
#include "../../Instancia.h"
#include "../../Bloque.h"



#include <iostream>
#include <math.h>
#include <string.h>
#include "../Archivo.h"
#include "../../Bloque.h"


using namespace std;

class ArchivoBloque: public Archivo {
public:

        //puede lanzar ExcepcionBloqueIncorrecto
        ArchivoBloque(string nombre);
        ~ArchivoBloque();
        void agregarAtributo(Atributo* atributo);
        int getCantidad();

        //puede lanzar ExcepcionOverflowTamBloque
        void escribir(list<Atributo>* datosAtributos,list<tamanioYTipoAtributo>* listaTipoAtributos);

        //puede lanzar ExcepcionOverflowTamBloque y ExcepcionBloqueInexistente
        int reescribir(Bloque* bloque, unsigned int numeroBloque);
        list<Atributo>* leer(int numeroRegistro, list<tamanioYTipoAtributo>* listaTipoAtributos);

        //puede lanzar ExcepcionBloqueInexistente
        int borrar(unsigned int numBloque);
        unsigned int getCantidadBloques();
        unsigned int getTamanoBloque();

private:
        int tamanio;
        int cantInstancias;
        int bloqueActual;
        Bloque** vectorBloques;
        //vector<Instancia> vectorInstancias;
       // vector<int> vectorAtributos;
        vector<char> vectorMapaBits;
        unsigned int tamanioBloque;
        unsigned int cantidadBloques;
        bool esMultiplo(int tamanioBloque);
        unsigned int siguientePosicionLibre(int tamanioInstancia);
        void leerMapaBloques();
        void escribirEspaciosLibres();
};

#endif

