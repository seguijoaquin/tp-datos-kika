#include "Entidad.h"


Entidad::Entidad(list<tamanioYTipoAtributo>* listaAtributos,string nombre, int ID,TipoArchivo tipoArchivo){
	this->listaAtributos = listaAtributos;
	this->instancias = new list<Instancia*>;
	this->nombre = nombre;
	this->ID = ID;
	int tam = 0;
	for(list<tamanioYTipoAtributo>::iterator it = listaAtributos->begin(); it != listaAtributos->end();it++){
		tam += it->cantidadBytes;
	}
	if (tipoArchivo == FIJO) this->archivo = new ArchivoRegistroFijo(nombre,tam);
	else if (tipoArchivo == VARIABLE) this->archivo = new ArchivoRegistroVariable(nombre);
	//else this->archivo = new ArchivoBloques(nombre);
}


Entidad::~Entidad(){
	delete this->listaAtributos;
	delete this->archivo;
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

void Entidad::crearInstancia(){
	list<Atributo>* listaDatos = new list<Atributo>;
	for(list<tamanioYTipoAtributo>::iterator it = this->listaAtributos->begin(); it != this->listaAtributos->end();it++){
		Atributo aux;
		if (it->tipo == ENTERO | it->tipo == ENTID){
			cout<<"Ingresar entero: ";
			cin>>aux.entero;
		} else {
			cout<<"Ingresar texto(max "<<it->cantidadBytes<<"): ";
			aux.texto = new char[maxCantidadCaracteres];
			cin>>aux.texto;
		}
		listaDatos->push_back(aux);
	}
	Instancia* instancia = new Instancia();
	instancia->setListaAtributos(listaDatos);
	this->instancias->push_back(instancia);
	this->archivo->escribir(listaDatos,this->listaAtributos);
}

void Entidad::leerInstancias(){
	for (int i = 0; i < this->archivo->getCantidad(); i++) {
		list<Atributo>* listaDatosAtributos = this->archivo->leer(i,this->listaAtributos);
		if (listaDatosAtributos != NULL) { //Si es null no hay ninguna instancia en ese registro/bloque (para fijos y bloques)

			if ((listaDatosAtributos->size() % this->listaAtributos->size()) == 0) {	//Se leyo una cant entera de instancias
				int cantidadInstancias = listaDatosAtributos->size() / this->listaAtributos->size();
				list<Atributo>::iterator it = listaDatosAtributos->begin();
				for (int i = 0; i < cantidadInstancias; i++) {
					Instancia* instancia = new Instancia();
					list<Atributo>* listaNueva = new list<Atributo>;
					for (unsigned int i = 0; i < this->listaAtributos->size() && it != listaDatosAtributos->end(); it++,i++) {
						listaNueva->push_back(*it);
					}
					instancia->setListaAtributos(listaNueva);
					this->instancias->push_back(instancia);
				}
				delete listaDatosAtributos;
			}
		}
	}
}

void Entidad::listarInstancias(){
	for (list<Instancia*>::iterator it = this->instancias->begin(); it != this->instancias->end(); it++) {
		list<tamanioYTipoAtributo>::iterator it3 = this->listaAtributos->begin();
		for (list<Atributo>::iterator it2 = (*it)->getListaAtributos()->begin(); it2 != (*it)->getListaAtributos()->end();it2++,it3++){
			if (it3->tipo == TEXTO) {
				cout<<it2->texto<<" ";
			} else {
				cout<<it2->entero<<" ";
			}
		}
		cout<<endl;
	}
}

void Entidad::borrar(int numero) {
	this->archivo->borrar(numero);
}

int Entidad::getCantidad(){
	return this->archivo->getCantidad();
}
