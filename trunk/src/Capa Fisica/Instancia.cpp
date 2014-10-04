#include "Instancia.h"


Instancia::Instancia(){

}

Instancia::~Instancia(){
	delete this->listaAtributos;
}

list<Atributo>* Instancia::getListaAtributos(){
	return this->listaAtributos;
}
