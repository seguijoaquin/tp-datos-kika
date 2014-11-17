#ifndef ADMIN_ENTIDADES
#define ADMIN_ENTIDADES

#include <iostream>
#include <list>
#include <sstream>
#include "Entidad.h"
#include "Archivos/Archivo.h"
#include <cstring>
#include <cstdlib>


using namespace std;

class AdministradorEntidades {
private:
	list<Entidad>* listaEntidades;
	int ultimoID;
	std::fstream archivo;
	void finalizarEntidad();
	void agregarDato(string buffer);
	void agregarDato(int buffer);
	void agregarAtributo(metaDataAtributo atributo);
public:
	AdministradorEntidades();
	~AdministradorEntidades();
	void menuUsuario();
	void leerArchivoEntidades();
	//void crearEntidad(Entidad* entidad);
	void crearInstancia(int id);
	int getUltimoID();
	int getID(int x);
	void listarEntidades();
	void listarInstancias(int id);
	Entidad* getEntidad(int id);
	void eliminarInstancia(unsigned int id, unsigned int id_instancia);
	void modificarInstancia(unsigned int id, unsigned int id_instancia);
	void eliminarInstancias(int id);
	bool entidadExistente(string nombre);
};

#endif
