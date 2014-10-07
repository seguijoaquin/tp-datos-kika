#ifndef INTERFAZ
#define INTERFAZ

#include <cstdlib>
#include <iostream>
#include <list>

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
