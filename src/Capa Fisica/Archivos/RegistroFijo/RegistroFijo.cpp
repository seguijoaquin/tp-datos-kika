#include "RegistroFijo.h"


ArchivoRegistroFijo::ArchivoRegistroFijo(string nombre){
	this->archivo.open(nombre.c_str(),ios::in | ios::out | ios::binary);
	if (!this->archivo) { //Si no existe
		this->archivo.open(nombre.c_str(),ios::in | ios::out | ios::binary | ios::trunc);
		this->cantRegistros = 0;
	} else {
		this->archivo.seekg(0,ios::beg);
		this->archivo.read((char*)&this->cantRegistros, sizeof(this->cantRegistros)); //El primer dato que hay en archivo es la cant de registros.
		this->archivo.read((char*)&this->tamanioRegistros,sizeof(this->tamanioRegistros)); //El segundo dato es el tamanio de cada registro.
	}
	this->nombreArchivo = nombre;
}

ArchivoRegistroFijo::~ArchivoRegistroFijo(){
	this->archivo.close();
}

list<Atributo>* ArchivoRegistroFijo::leer(int numeroRegistro, list<tamanioYTipoAtributo>* listaTipoAtributos){
	list<Atributo>* listaAtributos = new list<Atributo>;
	this->archivo.seekg(sizeof(this->cantRegistros) + sizeof(this->tamanioRegistros) + numeroRegistro * this->tamanioRegistros,ios::beg);

	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
		Atributo aux;
		if (it->tipo == TEXTO) {
			this->archivo.read((char*)&aux.texto,it->cantidadBytes);
		} else {
			this->archivo.read((char*)&aux.entero,it->cantidadBytes);
		}
		listaAtributos->push_back(aux);
	}
	return listaAtributos;
}

void ArchivoRegistroFijo::escribir(list<Atributo>* atributos,list<tamanioYTipoAtributo>* listaTipoAtributos){

	this->archivo.seekp(this->proximoEspacioLibre(),ios::beg);
	if (atributos->size() != listaTipoAtributos->size()) {
		//Tirar excepcion
	}
	list<Atributo>::iterator it2 = atributos->begin();
	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
		if (it->tipo == TEXTO) {
			this->archivo.write(it2->texto,it->cantidadBytes);
		} else {
			this->archivo.write((char*)&(it2->entero),it->cantidadBytes);
		}
		it2++;
	}

}

int ArchivoRegistroFijo::proximoEspacioLibre(){
	return 0;
}

int ArchivoRegistroFijo::getCantidad(){
	return this->cantRegistros;
}
