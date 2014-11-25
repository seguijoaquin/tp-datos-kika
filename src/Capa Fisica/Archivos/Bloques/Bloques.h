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
#include "../../Excepciones/ExcepcionBloqueInexistente.h"
#include "../../Excepciones/ExcepcionBloqueIncorrecto.h"
#include "../../Excepciones/ExcepcionOverflowTamBloque.h"

#define TAMANIOBLOQUE_DEFAULT 512


using namespace std;

class ArchivoBloque: public Archivo {
public:

        ArchivoBloque(string nombre,int tamanio);
        ~ArchivoBloque();
        void agregarAtributo(Atributo* atributo);
        int getCantidad();

        void escribir(list<Atributo>* datosAtributos,list<metaDataAtributo>* listaTipoAtributos);
        unsigned int escribir(char* bloque);
        list<Atributo>* leer(int numeroRegistro, list<metaDataAtributo>* listaTipoAtributos);
        void leer(char* &bloque, unsigned int numBloque);
        int modificarInstancia(int ID, list<Atributo>* atributos, list<metaDataAtributo>* listaTipoAtributos);
        int borrar(int numeroBloque);
        void reescribir(char* bloque, unsigned int posicion);
        unsigned int getCantidadBloques();
        unsigned int getTamanoBloque();

private:
        int bloqueActual;
        vector<Bloque*> vectorBloques;
        vector<char> vectorMapaBits;
        unsigned int tamanioBloque;
        unsigned int cantidadBloques;
        unsigned int siguientePosicionLibre(int tamanioInstancia);
        unsigned int siguientePosicionLibre();
        void leerMapaBloques();
        void escribirEspaciosLibres();
        int buscar(int idInstancia);
};

#endif

