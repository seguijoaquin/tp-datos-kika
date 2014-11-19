#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <cstdlib>
#include <iostream>
#include <list>
#include "Capa Fisica/Entidad.h"
#include "Capa Fisica/AdministradorEntidades.h"
#include "Capa Fisica/AdminIndicesSecundarios.h"
#include "Consultas.h"

using namespace std;

class Interfaz{

	private:
		list<string>* opciones;
		AdministradorEntidades* adminEntidades;
		AdministradorIndices* adminIndices;
		Consulta* consulta;
		//void crear_entidad();
		void crear_instancia();
		int seleccionar_entidad();
	
	public:
		Interfaz();
		~Interfaz();
		void listar_opciones();
		unsigned int pedir_opcion();
		bool ejecutar_opcion(unsigned int opc);
		void modificar_instancia();
		void eliminar_instancia();
		void eliminar_instancias();
		void listar_instancias();
		void administrar_indices_secundarios();
		int elegirEntidad();
};

#endif
