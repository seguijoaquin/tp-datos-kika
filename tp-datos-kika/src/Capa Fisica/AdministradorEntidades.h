#ifndef ADMIN_ENTIDADES
#define ADMIN_ENTIDADES

#include <iostream>
#include <list>
#include <sstream>
#include "Entidad.h"

using namespace std;

class AdministradorEntidades {
private:
	list<Entidad>* listaEntidades;
	int ultimoID;
	std::fstream archivo;
	void finalizarEntidad();
	void listarEntidades();
	void agregarDato(string buffer);
	void agregarDato(int buffer);
public:
	AdministradorEntidades();
	~AdministradorEntidades();
	void menuUsuario();
	void leerArchivoEntidades();
	void crearEntidad(Entidad* entidad);
	void crearInstancia();
	void modificarInstancia();
	int getUltimoID();
	int getID(int x);
};

#endif
