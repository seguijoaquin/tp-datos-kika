#ifndef ENTIDAD
#define ENTIDAD

#include "Instancia.h"
#include "Archivos/RegistroFijo/RegistroFijo.h"
#include "Archivos/RegistroVariable/RegistroVariable.h"
#include "Archivos/Bloques/Bloques.h"
#include "../Capa Logica/HashExtensible/Hash.h"

class Entidad {
private:
	list<metaDataAtributo>* listaAtributos;
	string nombre;
	int ID;
	int ultimoIDInstancia;
	TipoArchivo tipoArchivo;
	//Archivo* archivo;
	Hash* indice;
	//vector<Instancia*> instancias;
	int cantidadInstancias;
	void leerInstancias();
public:
	Entidad(list<metaDataAtributo>* listaAtributos,string nombre, int ID,TipoArchivo tipoArchivo);
	~Entidad();
	list<metaDataAtributo>* getListaAtributos();
	string getNombre();
	bool crearInstancia(list<Atributo>* listaDatos);
	int getUltimoIDInstancia();
	int getID();
	void listarInstancias();
	//int getCantidadInstancias();
	void listarAtributos();
	metaDataAtributo* getAtributo(unsigned int i);
	int getCantidad();
	int getTamanioMaxInstancia();
	bool eliminarInstancia(int id_instancia);
	void eliminarInstancias();
	void modificarInstancia(int id_instancia, list<Atributo>* newAtts);
	TipoArchivo getTipoArchivo();
	Instancia* getInstancia(int id, bool &error);
	int getCantidadInstancias();

};

#endif
