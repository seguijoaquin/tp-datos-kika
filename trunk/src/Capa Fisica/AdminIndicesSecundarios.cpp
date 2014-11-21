/*
 * AdminIndicesSecundarios.cpp
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */


#include "AdminIndicesSecundarios.h"
#include "../Capa Logica/ArbolBMas/ArbolBMas.h"

AdministradorIndices::AdministradorIndices(){
	this->arboles = new list<ArbolBMas>;
	this->hashes = new list<Hash>;
	this->rutaIndices = "\Indices Secundarios/";
	//leer archivo con arboles y hash e hidratar
}
AdministradorIndices::~AdministradorIndices(){

}

void AdministradorIndices::listar_indices(){
	for (list<ArbolBMas>:: iterator it = this->arboles->begin(); it != this->arboles->end(); ++it) {
		//listar nombres de arboles
	}
	for (list<Hash>::iterator it = this->hashes->begin(); it != this->hashes->end(); ++it) {
		//listar nombres hashes
	}

}

void AdministradorIndices::eliminar_indice(int x){

}

 void AdministradorIndices::crear_indice(Entidad* entidad){
	 cout << "Ingrese el nombre del indice secundario: " << endl;
	 string nombre;	 cin >> nombre;
	 cout << "Ingrese el tipo de estructura para el indice secundario:" << endl;
	 cout << "	1). Arbol B+" << endl;
	 cout << "	2). Hash" << endl;
	 int tipo; cin >> tipo;
	 ArbolBMas* arbol = NULL;
	 Hash* hash = NULL;
	 if (tipo==1) {
		 arbol = new ArbolBMas(this->rutaIndices+nombre);
	 } else {
		 hash = new Hash(this->rutaIndices+nombre,this->rutaIndices+nombre);
	 }
	 cout << "Ingrese los atributos que formaran parte del indice:" << endl;
	 entidad->listarAtributos();
	 int x; cin >> x;
	 metaDataAtributo* atributo = entidad->getAtributo(x);
	 //PEDIR MAS ATRIBUTOS
		 for (int i = 1; i <= entidad->getUltimoIDInstancia(); ++i) {
			bool error;
			Instancia* nuevaInstancia = entidad->getInstancia(i,error);
			if (!error) {
				Atributo* atributoInstancia = nuevaInstancia->getAtributo(x);
				if (atributo->tipo == TEXTO) {
					if (tipo==1) {
						arbol->agregarValor(*(new Clave(atributoInstancia->texto)),StringUtil::int2string(i));
					} else {
						hash->insertarElemento(atributoInstancia->texto,StringUtil::int2string(i));
					}
				} else {
					if (tipo==1){
						arbol->agregarValor(*(new Clave(StringUtil::int2string(atributoInstancia->entero))),StringUtil::int2string(i));
					} else {
						hash->insertarElemento(StringUtil::int2string(atributoInstancia->entero),StringUtil::int2string(i));
					}
				}
			}
		 }
	if (tipo == 1){
		this->arboles->push_back(*arbol);
	} else {
		this->hashes->push_back(*hash);
	}
}
