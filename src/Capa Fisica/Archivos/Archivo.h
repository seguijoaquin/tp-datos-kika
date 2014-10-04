#ifndef ARCHIVO
#define ARCHIVO

using namespace std;

#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include "../../constantes.h"

struct Atributo{
	int entero;	//Si es una instancia se guarda el ID
	char* texto;
};

enum TipoAtributo{
	ENTERO,
	TEXTO,
	ENTID	//entidad
};

enum TipoArchivo{
	FIJO,
	VARIABLE,
	BLOQUES
};

struct tamanioYTipoAtributo{
	TipoAtributo tipo;
	int cantidadBytes; //cantidad de bytes del tipo de Atributo
};

class Archivo {
private:

public:
	Archivo();
	virtual ~Archivo();

protected:
	fstream archivo;
	string nombreArchivo;
	virtual list<Atributo>* leer(int numero,list<tamanioYTipoAtributo>* listaTipoAtributos);
	virtual void escribir(list<Atributo>* atributos, list<tamanioYTipoAtributo>* listaTipoAtributos);
};

#endif
