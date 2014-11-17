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
 void AdministradorIndices::crear_indice(){
	 cout << "Ingrese el nombre del indice secundario: " << endl;
	 string nombre;	 cin >> nombre;
	 cout << "Ingrese el tipo de estructura para el indice secundario:" << endl;
	 cout << "1 - Arbol B+" << endl;
	 cout << "2 - Hash" << endl;
	 int opc; cin >> opc;
	 Estructura* estructura;
	 while (opc != 1 || opc != 2) { cin >>opc; }
	 switch (opc) {
	 	 case 1: estructura = new ArbolBMas(nombre);
	 		 break;
	 	 case 2:
	 		 break;
	 }

 }
