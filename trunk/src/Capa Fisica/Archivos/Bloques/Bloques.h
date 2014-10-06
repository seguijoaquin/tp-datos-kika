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

        ArchivoBloque(string nombre,int tamanio);
        ~ArchivoBloque();
        void agregarAtributo(Atributo* atributo);
        int getCantidad();

        void escribir(list<Atributo>* datosAtributos,list<tamanioYTipoAtributo>* listaTipoAtributos);

        list<Atributo>* leer(int numeroRegistro, list<tamanioYTipoAtributo>* listaTipoAtributos);

        void borrar(unsigned int numBloque);
        unsigned int getCantidadBloques();
        unsigned int getTamanoBloque();

private:
        int bloqueActual;
        vector<Bloque*> vectorBloques;
        unsigned int tamanioBloque;
        unsigned int cantidadBloques;
        bool esMultiplo(int tamanioBloque);
        unsigned int siguientePosicionLibre(int tamanioInstancia);
        void leerMapaBloques();
        void escribirEspaciosLibres();
};

#endif

