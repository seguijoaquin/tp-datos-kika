#include "RegistroVariable.h"


ArchivoRegistroVariable::ArchivoRegistroVariable(string nombre){
	this->archivo.open(nombre.c_str(),ios::in | ios::out | ios::binary);
	if (!this->archivo) { //Si no existe
		this->archivo.open(nombre.c_str(),ios::in | ios::out | ios::binary | ios::trunc);
		this->cantInstancias = 0;
	} else {
		this->archivo.seekg(0,ios::beg);
		this->archivo.read((char*)&this->cantInstancias, sizeof(this->cantInstancias)); //El primer dato que hay en archivo es la cant de registros.
	}
	this->nombreArchivo = nombre;

	this->leerMapaBits();
}

ArchivoRegistroVariable::~ArchivoRegistroVariable(){
	this->escribirMapaBits();
	archivo.seekp(0, ios::beg);
	archivo.write((char*)&this->cantInstancias, sizeof(this->cantInstancias));
	archivo.close();
}

void ArchivoRegistroVariable::leerMapaBits(){

	string dirMapaBits = this->nombreArchivo + "MapaBits";
	ifstream archivoMapaBits;
	archivoMapaBits.open(dirMapaBits.c_str(), fstream::binary);
    if(!archivoMapaBits) // si no existe, crear archivo nuevo
    	archivoMapaBits.open(dirMapaBits.c_str(), fstream::binary | fstream::app);

    espacioInstancia instancia;
    archivoMapaBits.seekg(0, ios::beg);
    archivoMapaBits.read((char*)&instancia.inicio, sizeof(instancia.inicio));

    while(!archivoMapaBits.eof()){
    	archivoMapaBits.read((char*)&instancia.fin, sizeof(instancia.fin));
    	this->vectorMapaBits.push_back(instancia);
    	archivoMapaBits.read((char*)&instancia.inicio, sizeof(instancia.inicio));
    }

    archivoMapaBits.close();
}

void ArchivoRegistroVariable::escribirMapaBits(){
	string dirMapaBits = nombreArchivo + "MapaBits";
	ofstream archivoMapaBits;
	archivoMapaBits.open(dirMapaBits.c_str(), fstream::binary);
	archivoMapaBits.seekp(0, ios::beg);
	for(unsigned int i = 0; i < vectorMapaBits.size(); i++) {
		archivoMapaBits.write((char*)&vectorMapaBits[i].inicio, sizeof(vectorMapaBits[i].inicio));
		archivoMapaBits.write((char*)&vectorMapaBits[i].fin, sizeof(vectorMapaBits[i].fin));
	}
	archivoMapaBits.close();
}

list<Atributo>* ArchivoRegistroVariable::leer(int numeroRegistro, list<tamanioYTipoAtributo>* listaTipoAtributos){
	list<Atributo>* listaAtributos = new list<Atributo>;
	if (numeroRegistro > this->cantInstancias) return NULL; // O throw exception

	this->archivo.seekg(this->vectorMapaBits[numeroRegistro].inicio,ios::beg);

	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
		Atributo aux;
		if (it->tipo == TEXTO) {
			char* buffer = new char[maxCantidadCaracteres + 1]; //+1 por separador
			int i = 0;
			this->archivo.read(&buffer[i],1);
			while (buffer[i] != separadorString && i < maxCantidadCaracteres) { //leo hasta encontrar caracter separador
				i++;
				this->archivo.read(&buffer[i],1);
			}
			if (buffer[i] == separadorString) {
				strcpy(aux.texto,buffer);
			} else {
				cout<<"Error leyendo"<<endl; //Hubo algun error
			}

		} else {
			this->archivo.read((char*)&aux.entero,it->cantidadBytes);
		}
		listaAtributos->push_back(aux);
	}
	return listaAtributos;
}

void ArchivoRegistroVariable::escribir(list<Atributo>* datosAtributos,list<tamanioYTipoAtributo>* listaTipoAtributos){

	if (datosAtributos->size() != listaTipoAtributos->size()) {
		return;//Tirar excepcion
	}

	int tamanioInstancia = 0;
	list<Atributo>::iterator it2 = datosAtributos->begin();
	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end();it++,it2++){
		if (it->tipo == TEXTO) {
			tamanioInstancia += strlen(it2->texto) + 1; //+1 por el caracter separador
		} else {
			tamanioInstancia += sizeof(it2->entero);
		}
	}
	int proximoEspacioLibre = this->proximoEspacioLibre(tamanioInstancia);
	this->archivo.seekp(proximoEspacioLibre,ios::beg);

	it2 = datosAtributos->begin();
	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++,it2++) {
		if (it->tipo == TEXTO) {
			this->archivo.write(it2->texto,strlen(it2->texto));
			this->archivo.write(&separadorString,1);
		} else {
			this->archivo.write((char*)&(it2->entero),it->cantidadBytes);
		}
	}
	this->cantInstancias++;
}

int ArchivoRegistroVariable::proximoEspacioLibre(int tamanioInstancia){

	vector<espacioInstancia>::iterator it = vectorMapaBits.begin();
	unsigned int i = 0;
	int espacioLibre = vectorMapaBits[i].inicio - sizeof(this->cantInstancias); //Primer espacio libre entre 1er dato de archivo(cantInstancias) y primer instancia
	if(espacioLibre >= tamanioInstancia){ //si el dato entra en uno de los espacios libres
		espacioInstancia espacio;
		espacio.inicio = sizeof(this->cantInstancias);
		espacio.fin = espacio.inicio + tamanioInstancia;
		vectorMapaBits.insert(it,espacio);
		return espacio.inicio;
	}
	it++;
	for(i=1; i< vectorMapaBits.size()  ; i++,it++){
		espacioLibre = vectorMapaBits[i].inicio - vectorMapaBits[i-1].fin;
		if(espacioLibre >= tamanioInstancia){ //si el dato entra en uno de los espacios libres

			espacioInstancia espacio;
			espacio.inicio = vectorMapaBits[i -1].fin;
			espacio.fin = espacio.inicio + tamanioInstancia;
			vectorMapaBits.insert(it,espacio);
			return espacio.inicio;
		}
	}
	//Si no encontro se ubica al final
	espacioInstancia espacio;
	espacio.inicio = vectorMapaBits[i -1].fin;
	espacio.fin = espacio.inicio + tamanioInstancia;
	vectorMapaBits.push_back(espacio);
	return espacio.inicio;
}

int ArchivoRegistroVariable::getCantidad(){
	return this->cantInstancias;
}

void ArchivoRegistroVariable::borrar(int numeroInstancia){
	vectorMapaBits.erase(vectorMapaBits.begin() + numeroInstancia);
	this->cantInstancias--;
}
