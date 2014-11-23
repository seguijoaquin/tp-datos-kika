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
	Indice* indice = new Indice();
	rewind(this->indicesCreados);
	char nombreArchivo[LARGO_CADENA];
	char nombreEntidad[LARGO_CADENA];
	char nombreAtributo[LARGO_CADENA];
	int tipoIndice, cantAtributos;
	list<string>* nombresAtributos = new list<string>;
	while(fscanf(this->indicesCreados,"%s", nombreArchivo) != EOF){
		fscanf(this->indicesCreados,"%d", &tipoIndice);
		fscanf(this->indicesCreados,"%s %d",nombreEntidad, &cantAtributos);
		indice->nombreArchivo = StringUtil::charToString(nombreArchivo);
		indice->tipo = tipoIndice;
		if(tipoIndice == ARBOL){
			indice->arbol = new ArbolBMas(rutaBaseIndiceSec + nombreArchivo);
			indice->hash  = NULL;
		}else{
			indice->hash  = new Hash(rutaBaseIndiceSec + nombreArchivo + rutaTabla,rutaBaseIndiceSec + nombreArchivo + rutaNodos);
			indice->arbol = NULL;
		}
		indice->nombreEntidad = StringUtil::charToString(nombreEntidad);

		for(int i = 0; i < cantAtributos; i++){
			fscanf(this->indicesCreados,"%s",nombreAtributo);
			nombresAtributos->push_back(nombreAtributo);
		}
		indice->nombresAtributos = nombresAtributos;
		nombresAtributos = new list<string>;
		this->indices->push_back(*indice);
		indice = new Indice();
	}
}

int AdministradorIndices::listar_indices(){
    list<Indice>::iterator it = this->indices->begin();
    int i = 0;
    while (it != this->indices->end()){
		cout << i << " - Indice secundario de entidad: "
						<< it->nombreEntidad << endl;
		cout << "\t \t Ordenado por: ";
		list<string>::iterator itNameAtt = it->nombresAtributos->begin();
		cout << *itNameAtt;
		while (itNameAtt != it->nombresAtributos->end()){
				++itNameAtt;
			if (itNameAtt != it->nombresAtributos->end()) cout << ", " << *itNameAtt;
		}
		cout << endl;
		++it;
		++i;
    }
    return i;
}

void AdministradorIndices::mostrar_indice(int x){
	list<Indice>::iterator it = this->indices->begin();
	for (int i = 0; i < x; ++i) {
		++it;
	}
	if (it->tipo == ARBOL) it->arbol->mostrarArbol();
	else it->hash->mostrarHash();
			//else it->hash->mostrarHash();
}
void AdministradorIndices::eliminar_indice(){
	int max = this->listar_indices();
	cout << "Elija el indice que desea eliminar:";
	int x; cin >> x;
	if (x <= max) {
		list<Indice>::iterator it = this->indices->begin();
		int i;
		for (i=0; i < x; ++i )	++it;
		this->indices->erase(it);
		this->actualizarIndices();
	}
}

void AdministradorIndices::actualizarIndices(){
	fclose(this->indicesCreados);
	this->indicesCreados = fopen("indicesCreados.txt","w+");
	list<Indice>::iterator it = this->indices->begin();
	while (it != this->indices->end()) {
		Indice indice;
		indice.arbol = it->arbol;
		indice.nombresAtributos = it->nombresAtributos;
		indice.hash = it->hash;
		indice.nombreArchivo = it->nombreArchivo;
		indice.nombreEntidad = it->nombreEntidad;
		indice.tipo = it->tipo;
		this->persistirIndice(&indice);
		++it;
	}

}

void AdministradorIndices::actualizar(Entidad* entidadVieja, Entidad* entidadNueva){
	list<Indice>::iterator it = this->indices->begin();
	list<metaDataAtributo>::iterator itAtributosEntidadNueva = entidadNueva->getListaAtributos();
	list<string>::iterator itAtributos;
	while (it != this->indices->end()) {
		if (it->nombreEntidad == entidadNueva->getNombre()) {
			string claveNueva;
			itAtributos = it->nombresAtributos->begin();
			while (itAtributos != it->nombresAtributos->end()) {
				if (itAtributos == itAtributosEntidadNueva->nombre) {
					claveNueva += itAtributosEntidadNueva->nombre;
					claveNueva += separadorClaves;
				}
				++itAtributos;
			}
			++itAtributosEntidadNueva;
		}
		++it;
	}
}

void AdministradorIndices::persistirIndice(Indice* indice){
	//[nombreArchivo tipoIndice nombreEntidad cantidadAtributos nombreAtributo+]
	fprintf(this->indicesCreados,"%s ",StringUtil::stringToChar(indice->nombreArchivo));
	fprintf(this->indicesCreados,"%i %s ", indice->tipo, StringUtil::stringToChar(indice->nombreEntidad));
	fprintf(this->indicesCreados,"%zu ",(indice->nombresAtributos)->size());
	list<string>::iterator itAtt = indice->nombresAtributos->begin();
	while(itAtt != indice->nombresAtributos->end()){
		fprintf(this->indicesCreados,"%s ",StringUtil::stringToChar(*itAtt));
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
	 metaDataAtributo* dataAtributo;
	 list<metaDataAtributo>* atts = new list<metaDataAtributo>;
	 list<int>* numeroAtts = new list<int>;
	 list<string>* nombresAtributos = new list<string>;

	 if (tipo==ARBOL)arbol = new ArbolBMas(rutaBaseIndiceSec + nombre);
	 else hash = new Hash(rutaBaseIndiceSec + nombre + rutaTabla,rutaBaseIndiceSec + nombre + rutaNodos);
	 cout << "Ingrese los atributos que formaran parte del indice:" << endl;
	 entidad->listarAtributos();
	 int x; cin >> x;
	 dataAtributo = entidad->getAtributo(x);
	 atts->push_back(*dataAtributo);
	 nombresAtributos->push_back((*dataAtributo).nombre);
	 numeroAtts->push_back(x);

	 //PEDIR MAS ATRIBUTOS
	 cout << "Desea agregar otro atributo? 1.Si / 2.No: ";
	 cin >> opc;
	 while(opc == 1){
		entidad->listarAtributos();
		cin >> x;
		dataAtributo = entidad->getAtributo(x);
		atts->push_back(*dataAtributo);
		nombresAtributos->push_back((*dataAtributo).nombre);
		numeroAtts->push_back(x);
		cout << "Desea agregar otro atributo? 1.Si / 2.No: ";
		cin >> opc;
	 }
	 indice.nombresAtributos = nombresAtributos;
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
				claveStr += separadorClaves;
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
