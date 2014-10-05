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

void Entidad::leerInstancias(){
	for (int i = 0; i < this->archivo->getCantidad(); i++) {
		list<Atributo>* listaDatosAtributos = this->archivo->leer(i,this->listaAtributos);
		if (listaDatosAtributos != NULL) { //Si es null no hay ninguna instancia en ese registro/bloque (para fijos y bloques)

			if (listaDatosAtributos->size() == this->listaAtributos->size()) {	//Se leyo una instancia
				Instancia* instancia = new Instancia();
				instancia->setListaAtributos(listaDatosAtributos);
				this->instancias->push_back(instancia);
			} else {		//Se leyo mas de una instancia (bloques)

				int cantidadInstancias = listaDatosAtributos->size() / this->listaAtributos->size();
				list<Atributo>::iterator it = listaDatosAtributos->begin();
				for (int i = 0; i < cantidadInstancias; i++) {
					Instancia* instancia = new Instancia();
					list<Atributo>* listaNueva = new list<Atributo>;
					for (int i = 0; i < this->listaAtributos->size() && it != listaDatosAtributos->end(); it++,i++) {
						listaNueva->push_back(*it);
					}
					instancia->setListaAtributos(listaNueva);
					this->instancias->push_back(instancia);
				}
			}
		}
	}
}
