#ifndef ARCHIVO
#define ARCHIVO

using namespace std;

#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
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
	DEBLOQUES
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
	virtual int getCantidad(); //Devuelve cantidad registros/instancias (para fijos/variables) o bloques en archivo
	//Para bloque, si se leen 2 instancias en un bloque y la entidad tiene 3 atributos, la lista que devuelve va a tener 6 elementos. Los primeros
	//tres de la 1era instancia y los otros tres de la 2da.
	virtual list<Atributo>* leer(int numero,list<tamanioYTipoAtributo>* listaTipoAtributos);	//numero = numero de registro/instancia/bloque.
	virtual void escribir(list<Atributo>* atributos, list<tamanioYTipoAtributo>* listaTipoAtributos);
	virtual void borrar(int numero);

protected:
	fstream archivo;
	string nombreArchivo;


};

#endif
