#ifndef ENTIDAD
#define ENTIDAD

#include "Instancia.h"

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

struct tamanioYTipoAtributo{
	TipoAtributo tipo;
	int cantidadBytes; //cantidad de bytes del tipo de Atributo
};

class Entidad {
private:
	list<tamanioYTipoAtributo>* listaAtributos;
	string nombre;
	int ID;
	TipoArchivo tipoArchivo;
	list<Instancia>* instancias;
public:
	Entidad(list<tamanioYTipoAtributo>* listaAtributos,string nombre, int ID);
	~Entidad();
	list<tamanioYTipoAtributo>* getListaAtributos();
	string getNombre();
	int getID();
};

#endif
