#include "Instancia.h"


Instancia::Instancia(){

}

Instancia::~Instancia(){
	delete this->listaAtributos;
}

list<Atributo>* Instancia::getListaAtributos(){
	return this->listaAtributos;
}

void Instancia::setListaAtributos(list<Atributo>* lista){
	this->listaAtributos = lista;
}
