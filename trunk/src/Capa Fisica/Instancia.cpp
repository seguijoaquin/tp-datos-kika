#include "Instancia.h"


Instancia::Instancia(list<metaDataAtributo>* listaMetaAtributos){
	this->listaAtributos = NULL;
	this->listaMetaAtributos = listaMetaAtributos;
}

Instancia::~Instancia(){
	delete this->listaAtributos;
}

list<Atributo>* Instancia::getListaAtributos(){
	return this->listaAtributos;
}

void Instancia::setListaAtributos(list<Atributo>* lista){
	if (this->listaAtributos != NULL) {
		this->listaAtributos->clear();
		delete this->listaAtributos;
	}
	this->listaAtributos = lista;
}

void Instancia::setListaMetaAtributos(list<metaDataAtributo>* listaMetaAtributos){
	this->listaMetaAtributos = listaMetaAtributos;
}

int Instancia::getID(){
	return this->listaAtributos->front().entero; //el 1er elemento es el ID
}

string Instancia::serializar(){
	string retorno;
	list<Atributo>::iterator it2 = this->listaAtributos->begin();
	for (list<metaDataAtributo>::iterator it = this->listaMetaAtributos->begin(); it != this->listaMetaAtributos->end(); it++,it2++) {
		if (it->tipo == TEXTO) {
			retorno += it2->texto;
		} else {
			retorno += StringUtil::int2string(it2->entero);
		}
		retorno += separadorCamposEntidades;
	}
	return retorno;
}

void Instancia::desSerializar(string aDeserealizar){
	this->listaAtributos = new list<Atributo>;
	vector<string> atributos = StringUtil::split(aDeserealizar,separadorCamposEntidades);
	list<Atributo>::iterator it2 = this->listaAtributos->begin();
	int cont = 0;
	for (list<metaDataAtributo>::iterator it = this->listaMetaAtributos->begin(); it != this->listaMetaAtributos->end(); it++,it2++) {
		Atributo atributo;
		if (it->tipo == TEXTO) {
			atributo.texto = new char[atributos.at(cont).length() + 1];
			strcpy(atributo.texto, atributos.at(cont).c_str());
		} else {
			atributo.entero = StringUtil::str2int(atributos.at(cont));
		}
		this->listaAtributos->push_back(atributo);
		cont++;
	}
}

Atributo* Instancia::getAtributo(int n){
	//Recibo el nombre de un atributo y devuelvo su valor
	//Por ejemplo, recibo "Color" y devuelvo "Rojo"
	int cont = 1;
	for (list<Atributo>::iterator it = this->listaAtributos->begin(); it != this->listaAtributos->end(); it++,cont++) {
		if (cont == n) {

			return &(*it);
		}
	}
	return NULL;
}

void Instancia::imprimir() {
	list<Atributo>::iterator it2 = this->listaAtributos->begin();
	for (list<metaDataAtributo>::iterator it = this->listaMetaAtributos->begin(); it != this->listaMetaAtributos->end(); it++,it2++) {
		if (it->tipo == TEXTO) {
			cout<<"Hello"<<endl;
			cout<<it->nombre<<": "<<it2->texto<<" ";
		} else {
			cout<<it->nombre<<": "<<it2->entero<<" ";
		}
	}
}
