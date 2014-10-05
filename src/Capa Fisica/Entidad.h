#ifndef ENTIDAD
#define ENTIDAD

#include "Instancia.h"

class Entidad {
private:
	list<tamanioYTipoAtributo>* listaAtributos;
	string nombre;
	int ID;
	TipoArchivo tipoArchivo;
	Archivo* archivo;
	list<Instancia*>* instancias;
public:
	Entidad(list<tamanioYTipoAtributo>* listaAtributos,string nombre, int ID);
	~Entidad();
	list<tamanioYTipoAtributo>* getListaAtributos();
	string getNombre();
	int getID();
	void leerInstancias();
};

#endif
