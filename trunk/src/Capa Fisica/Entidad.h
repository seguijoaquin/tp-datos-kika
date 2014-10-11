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
	void crearInstancia(list<Atributo>* listaDatos);
	int getUltimoIDInstancia();
	int getID();
	void leerInstancias();
	void listarInstancias();
	int getCantidadInstancias();
	Instancia* getInstancia(int id);
	int getCantidad();
	int getTamanioMaxInstancia();
	void eliminarInstancia(int id_instancia);
	void eliminarInstancias();
	void modificarInstancia(int id_instancia, list<metaDataAtributo>* metaAtts, list<Atributo>* newAtts);
	TipoArchivo getTipoArchivo();
};

#endif
