#include "Bloques.h"


ArchivoBloque::ArchivoBloque(string nombre) {
	int tamaniodebloque = 16 ; // esto esta hardcodeado, falta hacer un lector que lea el tamanio del bloque
	this->tamanioBloque = tamaniodebloque;
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
		char cantInstanciasBloque;
		char espacioLibreBloque;
		archivoMapaBloques.read((char*)&cantInstanciasBloque, sizeof(char));
		archivoMapaBloques.read((char*)&espacioLibreBloque, sizeof(char));
		while(!archivoMapaBloques.eof()){
			Bloque* bloque = new Bloque(this->tamanioBloque);
			bloque->setCantInstancias(cantInstanciasBloque);
			bloque->setEspacioLibre(espacioLibreBloque);
			this->vectorBloques.push_back(bloque);
			//this->vectorBloques[bloqueActual]->setCantInstancias(cantInstanciasBloque);
			//this->vectorBloques[bloqueActual]->setEspacioLibre( espacioLibreBloque);
			archivoMapaBloques.read((char*)&cantInstanciasBloque, sizeof(char));
			archivoMapaBloques.read((char*)&espacioLibreBloque, sizeof(char));
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
        	archivoMapaBloques.write((char*)(this->vectorBloques[i]->getCantInstancias()), sizeof(char));
        	archivoMapaBloques.write((char*)(this->vectorBloques[i]->getEspacioLibre()), sizeof(char));
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
	//this->archivo.write(&separadorInstancia,1);

//	//Bloque* bloque = new Bloque(this->tamanioBloque);
//	list<Atributo>::iterator it2 = datosAtributos->begin();
//
//	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
//		Atributo* atributo = new Atributo();
//		if (it->tipo == TEXTO) {
//			atributo->texto = it2->texto;
//			bloque->agregarAtributo(atributo);
//
//			//this->archivo.write(it2->texto,it->cantidadBytes);
//		} else {
//			cout<<it2->entero<<" "<<it->cantidadBytes<<endl;
//			atributo->entero = it2->entero;
//			bloque->agregarAtributo(atributo);
//			//this->archivo.write((char*)&it2->entero,it->cantidadBytes);
//		}
//		it2++;
//	}
//
//		//if(bloque->getTamanio() > tamanioBloque) return -1; // ERROR DE TAMANIO OVERFLOW EN EL BLOQUE
//
//        unsigned int posicion = this->siguientePosicionLibre();
//        archivo.seekp(sizeof(cantidadBloques) + posicion*tamanioBloque, ios::beg);
//        archivo.write((char*)bloque, sizeof(bloque));
//        cantidadBloques++;
//
//        //return posicion;
}

unsigned int ArchivoBloque::siguientePosicionLibre(int tamanioInstancia){

	for (int i = 0; i < this->cantidadBloques; i++){
		Bloque* bloque = this->vectorBloques[i];
		if(bloque->getEspacioLibre() > tamanioInstancia){
			this->bloqueActual = i;
			bloque->setEspacioLibre(bloque->getEspacioLibre() - tamanioInstancia);
			return (sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + (i * this->tamanioBloque) + (this->tamanioBloque - bloque->getEspacioLibre()));
		}
	}
	//Hay que crear bloque nuevo
	this->bloqueActual = cantidadBloques;
	this->cantidadBloques++;
	this->archivo.seekp(0,ios::end);
	char* x = new char[this->tamanioBloque];
	this->archivo.write(x,this->tamanioBloque);

	//Actualizo vectorBloques
	Bloque* bloque = new Bloque(this->tamanioBloque);
	bloque->setEspacioLibre(this->tamanioBloque - tamanioInstancia);
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
			Bloque* bloque = new Bloque(this->tamanioBloque);

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

