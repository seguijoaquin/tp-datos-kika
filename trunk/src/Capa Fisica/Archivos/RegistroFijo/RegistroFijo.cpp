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

	this->leerMapaBits();
}

ArchivoRegistroFijo::~ArchivoRegistroFijo(){
	this->escribirMapaBits();
	archivo.seekp(0, ios::beg);
	archivo.write((char*)&this->cantRegistros, sizeof(this->cantRegistros));
	archivo.write((char*)&this->tamanioRegistros, sizeof(this->tamanioRegistros));
	archivo.close();
}

void ArchivoRegistroFijo::leerMapaBits(){

	string dirMapaBits = this->nombreArchivo + "MapaBits";
	ifstream archivoMapaBits;
	archivoMapaBits.open(dirMapaBits.c_str(), fstream::binary);
    if(!archivoMapaBits) // si no existe, crear archivo nuevo
    	archivoMapaBits.open(dirMapaBits.c_str(), fstream::binary | fstream::app);

    char bit;
    archivoMapaBits.read((char*)&bit, sizeof(char));
    while(!archivoMapaBits.eof()){
    	vectorMapaBits.push_back(bit);
    	archivoMapaBits.read((char*)&bit, sizeof(char));
    }

    archivoMapaBits.close();
}

void ArchivoRegistroFijo::escribirMapaBits(){
	string dirMapaBits = nombreArchivo + "MapaBits";
	ofstream archivoMapaBits;
	archivoMapaBits.open(dirMapaBits.c_str(), fstream::binary);
	archivoMapaBits.seekp(0, ios::beg);
	for(int i = 0; i < vectorMapaBits.size(); i++)
		archivoMapaBits.write((char*)&vectorMapaBits[i], sizeof(char));
	archivoMapaBits.close();
}

list<Atributo>* ArchivoRegistroFijo::leer(int numeroRegistro, list<tamanioYTipoAtributo>* listaTipoAtributos){
	list<Atributo>* listaAtributos = new list<Atributo>;
	if (numeroRegistro > this->cantRegistros) return NULL; // O throw exception
	if (this->vectorMapaBits.at(numeroRegistro) == '0') return NULL;

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

void ArchivoRegistroFijo::escribir(list<Atributo>* datosAtributos,list<tamanioYTipoAtributo>* listaTipoAtributos){

	this->archivo.seekp(sizeof(this->cantRegistros) + sizeof(this->tamanioRegistros) + this->proximoEspacioLibre() * this->tamanioRegistros,ios::beg);
	if (datosAtributos->size() != listaTipoAtributos->size()) {
		return;//Tirar excepcion
	}
	list<Atributo>::iterator it2 = datosAtributos->begin();
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

	int pos;
	for(pos = 0; pos < vectorMapaBits.size() && vectorMapaBits[pos] == '1'; pos++){};
	if(pos == vectorMapaBits.size()) {
	     vectorMapaBits.push_back('1');
	     this->cantRegistros++;
	}
	else {
		vectorMapaBits[pos] = '1';
	}
	return pos;
}

int ArchivoRegistroFijo::getCantidad(){
	return this->cantRegistros;
}

void ArchivoRegistroFijo::borrar(int numeroRegistro){
	if(numeroRegistro >= vectorMapaBits.size()) {return; }//O tiro excepcion

	vectorMapaBits[numeroRegistro] = '0' ;
}
