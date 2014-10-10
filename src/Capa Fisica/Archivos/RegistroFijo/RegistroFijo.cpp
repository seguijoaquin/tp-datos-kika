#include "RegistroFijo.h"


ArchivoRegistroFijo::ArchivoRegistroFijo(string nombre, int tam){
	this->tamanioRegistros = tam;
	this->archivo.open(nombre.c_str(),fstream::in | fstream::out | fstream::binary);
	if (!this->archivo) { //Si no existe
		this->archivo.open(nombre.c_str(),fstream::in | fstream::out | fstream::binary | fstream::trunc);
		this->cantRegistros = 0;
		this->archivo.seekp(0,ios::beg);
		archivo.write((char*)&this->cantRegistros, sizeof(this->cantRegistros));
		archivo.write((char*)&this->tamanioRegistros, sizeof(this->tamanioRegistros));
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

list<Atributo>* ArchivoRegistroFijo::leer(int numeroRegistro, list<metaDataAtributo>* listaTipoAtributos){
	list<Atributo>* listaAtributos = new list<Atributo>;
	if (numeroRegistro > this->cantRegistros) return NULL; // O throw exception
	if (this->vectorMapaBits.at(numeroRegistro) == '0') return NULL;

	this->archivo.seekg(sizeof(this->cantRegistros) + sizeof(this->tamanioRegistros) + numeroRegistro * this->tamanioRegistros,ios::beg);

	for (list<metaDataAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
		Atributo aux;
		if (it->tipo == TEXTO) {
			aux.texto = new char[it->cantidadBytes];
			this->archivo.read(aux.texto,it->cantidadBytes);
		} else {
			this->archivo.read((char*)&aux.entero,it->cantidadBytes);
		}
		listaAtributos->push_back(aux);
	}
	return listaAtributos;
}

void ArchivoRegistroFijo::escribir(list<Atributo>* datosAtributos,list<metaDataAtributo>* listaTipoAtributos){

	this->archivo.seekp(sizeof(this->cantRegistros) + sizeof(this->tamanioRegistros) + this->proximoEspacioLibre() * this->tamanioRegistros,ios::beg);
	if (datosAtributos->size() != listaTipoAtributos->size()) {
		return;//Tirar excepcion
	}
	list<Atributo>::iterator it2 = datosAtributos->begin();
	for (list<metaDataAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
		if (it->tipo == TEXTO) {
			this->archivo.write(it2->texto,it->cantidadBytes);
		} else {
			this->archivo.write((char*)&it2->entero,it->cantidadBytes);
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

int ArchivoRegistroFijo::borrar(int IDInstancia){
	bool encontrado = false;
	for (int i = 0; (i < this->getCantidad()) && (!encontrado);i++){
		if (vectorMapaBits[i] == '1') {
			this->archivo.seekg(sizeof(this->cantRegistros) + sizeof(this->tamanioRegistros) + i * this->tamanioRegistros,ios::beg);
			int ID;
			this->archivo.read((char*)&ID,sizeof(ID));
			if (ID == IDInstancia) {
				encontrado = true;
				this->vectorMapaBits[i] = '0';
				return 1;
			}
		}
	}
	return 0;

	/*if(numeroRegistro >= vectorMapaBits.size()) {return; }//O tiro excepcion

	vectorMapaBits[numeroRegistro] = '0' ;*/
}

int ArchivoRegistroFijo::modificarInstancia(int ID, list<Atributo>* atributos, list<metaDataAtributo>* listaTipoAtributos){
	int pos = this->buscar(ID);
	if (pos != -1) {
		this->archivo.seekp(pos,ios::beg);
		list<Atributo>::iterator it2 = atributos->begin();
		for (list<metaDataAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
			if (it->tipo == TEXTO) {
				this->archivo.write(it2->texto,it->cantidadBytes);
			} else {
				this->archivo.write((char*)&it2->entero,it->cantidadBytes);
			}
			it2++;
		}
		return 1;
	}
	return -1;
}

int ArchivoRegistroFijo::buscar(int IDInstancia){
	bool encontrado = false;
	int ID,posActual;
	for (unsigned int i = 0; (i < this->cantRegistros) && (!encontrado); i++) {
		this->archivo.seekg(sizeof(this->cantRegistros) + sizeof(this->tamanioRegistros) + i * this->tamanioRegistros,ios::beg);
		posActual = this->archivo.tellg();
		this->archivo.read((char*)&ID,sizeof(ID));
		if (ID == IDInstancia) {
			return posActual;
		}
	}
	return -1;
}
