#include "Entidad.h"


Entidad::Entidad(list<atributo>* listaAtributos,string nombre, int ID){
	this->listaAtributos = listaAtributos;
	this->nombre = nombre;
	this->ID = ID;
}


Entidad::~Entidad(){
	delete this->listaAtributos;
}

list<atributo>* Entidad::getListaAtributos(){
	return this->listaAtributos;
}

string Entidad::getNombre(){
	return this->nombre;
}

int Entidad::getID(){
	return this->ID;
}
