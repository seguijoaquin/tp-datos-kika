#ifndef ENTIDAD
#define ENTIDAD

#include "Instancia.h"
#include "Archivos/RegistroFijo/RegistroFijo.h"
#include "Archivos/RegistroVariable/RegistroVariable.h"
#include "Archivos/Bloques/Bloques.h"


class Entidad {
private:
	list<metaDataAtributo>* listaAtributos;
	string nombre;
	int ID;
	int ultimoIDInstancia;
	TipoArchivo tipoArchivo;
	Archivo* archivo;
	vector<Instancia*> instancias;
public:
	Entidad(list<metaDataAtributo>* listaAtributos,string nombre, int ID,TipoArchivo tipoArchivo);
	~Entidad();
	list<metaDataAtributo>* getListaAtributos();
	string getNombre();
	void crearInstancia();
	int getID();
	void leerInstancias();
	void listarInstancias();
	void borrar(int numero);
	int getCantidad();
	int getTamanioMaxInstancia();
};

#endif
