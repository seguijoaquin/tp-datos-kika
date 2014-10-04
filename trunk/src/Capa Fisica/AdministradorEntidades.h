#ifndef ADMIN_ENTIDADES
#define ADMIN_ENTIDADES

#include <iostream>
#include <list>
#include "Entidad.h"

using namespace std;

class AdministradorEntidades {
private:
	list<Entidad>* listaEntidades;
	int ultimoID;
public:
	AdministradorEntidades();
	~AdministradorEntidades();
	void menuUsuario();
	void leerArchivoEntidades();
	void crearEntidad();
	void crearInstancia();
	void modificarInstancia();
};

#endif
