#include "Bloques.h"


ArchivoBloque::ArchivoBloque(string nombre, int tamanio) {
	this->tamanioBloque = maxInstanciasEnBloque * tamanio;
	this->bloqueActual = 0;
    archivo.open(nombre.c_str(), fstream::in | fstream::out | fstream::binary);
    if(!archivo){ // si no existe, crear archivo nuevo
        archivo.open(nombre.c_str(), fstream::in | fstream::out | fstream::binary | fstream::trunc);
        cantidadBloques=0;
    }else{
        archivo.seekg(0, ios::beg);
        archivo.read((char*)&cantidadBloques, sizeof(cantidadBloques));
		archivo.read((char*)&this->tamanioBloque,sizeof(this->tamanioBloque)); //El segundo dato es el tamanio de cada registro.

    }
    nombreArchivo = nombre;

    leerMapaBloques();
}

ArchivoBloque::~ArchivoBloque() {
        escribirEspaciosLibres();
        archivo.seekp(0, ios::beg);
        archivo.write((char*)&cantidadBloques, sizeof(cantidadBloques));
        archivo.write((char*)&tamanioBloque, sizeof(tamanioBloque));
        archivo.close();
}

bool ArchivoBloque::esMultiplo(int tamanio){

        double n1= tamanio / 512;
        double n2= log2(n1);

        return((n2 == static_cast<int>(n2)) && (tamanio>=512));
}

void ArchivoBloque::leerMapaBloques(){

        string dirMapaBloques = nombreArchivo + "MapaBloques";
        ifstream archivoMapaBloques;
        archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary);
        if(!archivoMapaBloques) // si no existe, crear archivo nuevo
        	archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary | fstream::app);

        int bloqueActual = 0;
		int cantInstanciasBloque;
		int espacioLibreBloque;
		archivoMapaBloques.read((char*)&cantInstanciasBloque, sizeof(cantInstanciasBloque));
		archivoMapaBloques.read((char*)&espacioLibreBloque, sizeof(espacioLibreBloque));
		while(!archivoMapaBloques.eof()){
			Bloque* bloque = new Bloque(this->tamanioBloque);
			bloque->setCantInstancias(cantInstanciasBloque);
			bloque->setEspacioLibre(espacioLibreBloque);
			this->vectorBloques.push_back(bloque);
			archivoMapaBloques.read((char*)&cantInstanciasBloque, sizeof(cantInstanciasBloque));
			archivoMapaBloques.read((char*)&espacioLibreBloque, sizeof(espacioLibreBloque));
			bloqueActual++;
		}

		archivoMapaBloques.close();
}

void ArchivoBloque::escribirEspaciosLibres(){

        string dirMapaBloques = nombreArchivo + "MapaBloques";
        ofstream archivoMapaBloques;
        archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary);
        archivoMapaBloques.seekp(0, ios::beg);

        for(unsigned int i=0; i< this->cantidadBloques; i++){
        	int cantInstancias = this->vectorBloques[i]->getCantInstancias();
        	int espacioLibre = this->vectorBloques[i]->getEspacioLibre();
        	archivoMapaBloques.write((char*)&cantInstancias, sizeof(this->vectorBloques[i]->getCantInstancias()));
        	archivoMapaBloques.write((char*)&espacioLibre, sizeof(this->vectorBloques[i]->getEspacioLibre()));
        }

        archivoMapaBloques.close();
}

void ArchivoBloque::escribir(list<Atributo>* datosAtributos,list<tamanioYTipoAtributo>* listaTipoAtributos){

	int tamanioInstancia = 0;
	list<Atributo>::iterator it2 = datosAtributos->begin();
	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end();it++,it2++){
		if (it->tipo == TEXTO) {
			tamanioInstancia += strlen(it2->texto) + 1; //+1 por el caracter separador
		} else {
			tamanioInstancia += sizeof(it2->entero);
		}
	}

	//tamanioInstancia+=1; //Por caracter separador instancias.
	int proximoEspacioLibre = this->siguientePosicionLibre(tamanioInstancia);
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
	this->vectorBloques[this->bloqueActual]->incrementarInstancias();
	this->vectorBloques[this->bloqueActual]->setEspacioLibre(this->vectorBloques[this->bloqueActual]->getEspacioLibre() - tamanioInstancia);
}

unsigned int ArchivoBloque::siguientePosicionLibre(int tamanioInstancia){

	for (unsigned int i = 0; i < this->cantidadBloques; i++){
		Bloque* bloque = this->vectorBloques[i];
		if(bloque->getEspacioLibre() >= tamanioInstancia){
			this->bloqueActual = i;
			return (sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + (i * this->tamanioBloque) + (this->tamanioBloque - bloque->getEspacioLibre()));
		}
	}
	//Hay que crear bloque nuevo
	this->bloqueActual = cantidadBloques;
	this->cantidadBloques++;
	//Actualizo vectorBloques
	Bloque* bloque = new Bloque(this->tamanioBloque);
	bloque->setCantInstancias(0);
	this->vectorBloques.push_back(bloque);

	return (sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + this->bloqueActual * this->tamanioBloque);
}

list<Atributo>* ArchivoBloque::leer(int numeroBloque, list<tamanioYTipoAtributo>* listaTipoAtributos){

	list<Atributo>* listaAtributos = new list<Atributo>;
	if (numeroBloque > this->cantidadBloques) return NULL; // O throw exception
	if (this->vectorBloques[numeroBloque]->getCantInstancias() == 0) return NULL;
	this->archivo.seekg(sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + numeroBloque * this->tamanioBloque,ios::beg);
	for(int i = 0; i < this->vectorBloques[numeroBloque]->getCantInstancias(); i++) {
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
					aux.texto = new char[i+1];
					strncpy(aux.texto,buffer,i);
					aux.texto[i] = NULL;
				} else {
					cout<<"Error leyendo"<<endl; //Hubo algun error
				}
			} else {
				this->archivo.read((char*)&aux.entero,it->cantidadBytes);
			}
			listaAtributos->push_back(aux);
		}
	}
	return listaAtributos;

}

unsigned int ArchivoBloque::getCantidadBloques(){
        return cantidadBloques;
}

int ArchivoBloque::getCantidad(){
        return cantidadBloques;
}

unsigned int ArchivoBloque::getTamanoBloque(){
        return tamanioBloque;
}

void ArchivoBloque::borrar(unsigned int numBloque){
		/*
        if(numBloque >= vectorMapaBits.size()) return -1; // ERROR

        vectorMapaBits.at(numBloque) = '0' ;
        cantidadBloques--;
        return 1; // termina bien
        */
}

