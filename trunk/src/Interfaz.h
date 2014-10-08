#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <cstdlib>
#include <iostream>
#include <list>
#include "Capa Fisica/Entidad.h"

using namespace std;

class Interfaz{

	private:
		list<string>* opciones;
		void crear_entidad();
		void crear_instancia();
	
	public:
		Interfaz();
		void listar_opciones();
		unsigned int pedir_opcion();
		bool ejecutar_opcion(unsigned int opc);

};

#endif