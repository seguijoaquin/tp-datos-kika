/*
 * AdminIndicesSecundarios.cpp
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */


#include "AdminIndicesSecundarios.h"
#include "../Capa Logica/ArbolBMas/ArbolBMas.h"

AdministradorIndices::AdministradorIndices(){
	this->indices = new list<Indice>;
	this->indicesCreados = fopen("indicesCreados.txt","r+b");
	if(!this->indicesCreados)this->indicesCreados = fopen("indicesCreados.txt","w+");
	this->inicializarIndices();
}
AdministradorIndices::~AdministradorIndices(){
	list<Indice>::iterator it = this->indices->begin();
	while (it != this->indices->end()){
		if(it->tipo == ARBOL) delete it->arbol;
		else delete it->hash;
		++it;
	}
	fclose(this->indicesCreados);
}

void AdministradorIndices::inicializarIndices(){
	rewind(this->indicesCreados);
	char* nombreArchivo, nombreEntidad;
	int tipoIndice, cantAtributos;
	fscanf(this->indicesCreados,"%s %i %s %i", nombreArchivo,tipoIndice,nombreEntidad, cantAtributos);
//Leer el archivo this->indicesCreados
//Crear arboles y hash depende tipoIndice con nombreArchivo
//Guardo arbol o hash en indice
//Agrego indice a lista de indices
}

void AdministradorIndices::listar_indices(){
	list<Indice>::iterator it = this->indices->begin();
	int i = 1;
	while (it != this->indices->end()){
		cout << i << " - Indice secundario de entidad: "
				<< it->nombreEntidad << endl;
		cout << "Ordenado por:";
		list<metaDataAtributo>::iterator itMetaData = it->atributos->begin();
		while (itMetaData != it->atributos->end()){
			cout << itMetaData->nombre << "; ";
			++itMetaData;
		}
		cout << endl;
		++it;
		++i;
	}
}

void AdministradorIndices::eliminar_indice(int x){

}

void AdministradorIndices::persistirIndice(Indice* indice){
	//[nombreArchivo tipoIndice nombreEntidad cantidadAtributos nombreAtributo+]
	fprintf(this->indicesCreados,"%s ",StringUtil::stringToChar(indice->nombreArchivo));
	fprintf(this->indicesCreados,"%i %s ", indice->tipo, StringUtil::stringToChar(indice->nombreEntidad));
	fprintf(this->indicesCreados,"%zu ",(indice->atributos)->size());
	list<metaDataAtributo>::iterator itAtt = indice->atributos->begin();
	while(itAtt != indice->atributos->end()){
		fprintf(this->indicesCreados,"%s ",StringUtil::stringToChar(itAtt->nombre));
		++itAtt;
	}
	fprintf(this->indicesCreados,"\n");
}

 void AdministradorIndices::crear_indice(Entidad* entidad){
	 Indice indice;
	 indice.nombreEntidad = entidad->getNombre();
	 cout << "Ingrese el nombre del indice secundario: " << endl;
	 string nombre;	 cin >> nombre;
	 indice.nombreArchivo = nombre;
	 cout << "Ingrese el tipo de estructura para el indice secundario:" << endl;
	 cout << "	1). Arbol B+" << endl;
	 cout << "	2). Hash" << endl;
	 int tipo, opc; cin >> tipo;
	 indice.tipo = tipo;
	 ArbolBMas* arbol = NULL;
	 Hash* hash = NULL;
	 list<metaDataAtributo>* atts = new list<metaDataAtributo>;
	 list<int>* numeroAtts = new list<int>;

	 if (tipo==ARBOL)arbol = new ArbolBMas(nombre);
	 else hash = new Hash(nombre,nombre);

	 cout << "Ingrese los atributos que formaran parte del indice:" << endl;
	 entidad->listarAtributos();
	 int x; cin >> x;
	 atts->push_back(*entidad->getAtributo(x));
	 numeroAtts->push_back(x);

	 //PEDIR MAS ATRIBUTOS
	 cout << "Desea agregar otro atributo? 1.Si / 2.No: ";
	 cin >> opc;
	 while(opc == 1){
		entidad->listarAtributos();
		cin >> x;
		atts->push_back(*entidad->getAtributo(x));
		numeroAtts->push_back(x);
		cout << "Desea agregar otro atributo? 1.Si / 2.No: ";
		cin >> opc;
	 }
	 indice.atributos = atts;
	 string claveStr = "";
	 Atributo* atributoInstancia;
	 for (int i = 1; i <= entidad->getUltimoIDInstancia(); ++i) {//i es el ID de la instancia
		bool error;
		Instancia* nuevaInstancia = entidad->getInstancia(i,error);
		string claveStr = "";
		if (!error) {
			// CONCATENA CLAVES
			list<metaDataAtributo>::iterator itAtt = atts->begin();
			list<int>::iterator itNum = numeroAtts->begin();
			while(itAtt != atts->end()){
				atributoInstancia = nuevaInstancia->getAtributo(*itNum);
				if (itAtt->tipo == TEXTO) {
					claveStr += atributoInstancia->texto;
				} else {
					claveStr += StringUtil::int2string(atributoInstancia->entero);
				}
				++itAtt;
				++itNum;
			}
			// AGREGA VALOR CON CLAVE CONCATENADA.
			if (tipo==ARBOL) {
				arbol->agregarValor(*(new Clave(claveStr)),StringUtil::int2string(i));
			} else {
				hash->insertarElemento(claveStr,StringUtil::int2string(i));
			}
		}
	 }
	if (tipo == ARBOL){
		arbol->persistir();
		indice.hash = NULL;
		indice.arbol = arbol;
		this->indices->push_back(indice);
	} else {
		indice.arbol = NULL;
		indice.hash = hash;
		this->indices->push_back(indice);
	}
	this->persistirIndice(&indice);
}
