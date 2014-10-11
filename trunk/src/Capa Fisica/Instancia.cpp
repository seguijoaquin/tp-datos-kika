#include "Instancia.h"


Instancia::Instancia(){
	this->listaAtributos = NULL;
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

int Instancia::getID(){
	return this->listaAtributos->front().entero; //el 1er elemento es el ID
}
