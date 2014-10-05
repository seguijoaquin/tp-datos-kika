#ifndef ENTIDAD
#define ENTIDAD

#include "Instancia.h"
#include "Archivos/RegistroFijo/RegistroFijo.h"
#include "Archivos/RegistroVariable/RegistroVariable.h"
#include "Archivos/Bloques/Bloques.h"


class Entidad {
private:
	list<tamanioYTipoAtributo>* listaAtributos;
	string nombre;
	int ID;
	TipoArchivo tipoArchivo;
	Archivo* archivo;
	list<Instancia*>* instancias;
public:
	Entidad(list<tamanioYTipoAtributo>* listaAtributos,string nombre, int ID,TipoArchivo tipoArchivo);
	~Entidad();
	list<tamanioYTipoAtributo>* getListaAtributos();
	string getNombre();
	void crearInstancia();
	int getID();
	void leerInstancias();
	void listarInstancias();
	void borrar(int numero);
	int getCantidad();
};

#endif
