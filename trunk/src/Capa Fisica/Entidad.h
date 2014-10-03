#ifndef ENTIDAD
#define ENTIDAD

#include <iostream>
#include <list>
#include <string.h>

using namespace std;

enum tipoAtributo{
	ENTERO,
	STRING,
	INSTANCIA
};

struct atributo{
	tipoAtributo tipo;
	int cantidadID; //cantidad de bytes si es entero/string, ID si es entidad
};

class Entidad {
private:
	list<atributo>* listaAtributos;
	string nombre;
	int ID;
public:
	Entidad(list<atributo>* listaAtributos,string nombre, int ID);
	~Entidad();
	list<atributo>* getListaAtributos();
	string getNombre();
	int getID();
};

#endif
