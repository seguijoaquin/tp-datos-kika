/*
 * AdminIndicesSecundarios.cpp
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */


#include "AdminIndicesSecundarios.h"
#include "../Capa Logica/ArbolBMas/ArbolBMas.h"

void AdministradorIndices::listar_indices(){

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
	 //VALIDAR SI INGRESA HASH O ARBOL
	 ArbolBMas* estructura = new ArbolBMas(nombre);
	 cout << "Ingrese los atributos que formaran parte del indice:" << endl;
	 entidad->listarAtributos();
	 int att; cin >> att;
	 metaDataAtributo* atributo = entidad->getAtributo(att);
	 //PEDIR MAS ATRIBUTOS
	 for (int i = 0; i < 100; ++i) {
		bool error;
		entidad->getInstancia(i,error);
		if (!error) {
			 estructura->agregarValor(*(new Clave(atributo->nombre)),StringUtil::int2string(i));
				}
	 }
	estructura->persistir();
	estructura->mostrarArbol();
}
