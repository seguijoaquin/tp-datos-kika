/*
 * AdminIndicesSecundarios.cpp
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */


#include "AdminIndicesSecundarios.h"
#include "../Capa Logica/ArbolBMas/ArbolBMas.h"

void AdministradorIndices::listar_indices(){
//	list<Estructura>::iterator it;
//	int x = 1;
//	for (it = this->indices->begin(); it != this->indices->end(); ++it) {
//		cout << x << " - " << it->getNombre() << endl;
//		++x;
//	}
}

void AdministradorIndices::eliminar_indice(int x){

}
 void AdministradorIndices::crear_indice(Entidad* entidad){
	 cout << "Ingrese el nombre del indice secundario: " << endl;
	 string nombre;	 cin >> nombre;
	 cout << "Ingrese el tipo de estructura para el indice secundario:" << endl;
	 cout << "1 - Arbol B+" << endl;
	 cout << "2 - Hash" << endl;
	 int tipo; cin >> tipo;
	 Estructura* estructura;
	 while (tipo != 1 || tipo != 2) { cin >>tipo; }
	 switch (tipo) {
	 	 case 1: estructura = new ArbolBMas(nombre);
	 		 break;
	 	 case 2: //HACER UN NEW HASHHHHHHHHHHH
	 		 break;
	 }
	 cout << "Ingrese los atributos que formaran parte del indice:" << endl;
	 //listar atributos y elegir uno
	 //preguntar si se quiere elegir mas atributos

}