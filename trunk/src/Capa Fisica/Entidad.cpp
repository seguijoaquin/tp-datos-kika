#include "Entidad.h"


Entidad::Entidad(list<tamanioYTipoAtributo>* listaAtributos,string nombre, int ID){
	this->listaAtributos = listaAtributos;
	this->nombre = nombre;
	this->ID = ID;
}


Entidad::~Entidad(){
	delete this->listaAtributos;
}

list<tamanioYTipoAtributo>* Entidad::getListaAtributos(){
	return this->listaAtributos;
}

string Entidad::getNombre(){
	return this->nombre;
}

int Entidad::getID(){
	return this->ID;
}
