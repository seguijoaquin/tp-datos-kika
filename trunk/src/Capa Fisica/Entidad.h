#ifndef ENTIDAD
#define ENTIDAD

#include <iostream>
#include <list>
#include <string.h>

using namespace std;

enum TipoAtributo{
	ENTERO,
	STRING,
	INSTANCIA
};

enum TipoArchivo{
	FIJO,
	VARIABLE,
	BLOQUES
};

struct atributo{
	TipoAtributo tipo;
	int cantidadID; //cantidad de bytes si es entero/string, ID si es entidad
};

class Entidad {
private:
	list<atributo>* listaAtributos;
	string nombre;
	int ID;
	TipoArchivo tipoArchivo;
public:
	Entidad(list<atributo>* listaAtributos,string nombre, int ID);
	~Entidad();
	list<atributo>* getListaAtributos();
	string getNombre();
	int getID();
};

#endif
