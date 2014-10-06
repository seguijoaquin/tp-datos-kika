#include "Bloques.h"


ArchivoBloque::ArchivoBloque(string nombre) {
	int tamaniodebloque = 16 ; // esto esta hardcodeado, falta hacer un lector que lea el tamanio del bloque
	this->tamanio = tamaniodebloque;
    archivo.open(nombre.c_str(), fstream::in | fstream::out | fstream::binary);
    if(!archivo){ // si no existe, crear archivo nuevo
        archivo.open(nombre.c_str(), fstream::in | fstream::out | fstream::binary | fstream::trunc);
        cantidadBloques=0;
    }else{
        archivo.seekg(0, ios::beg);
        archivo.read((char*)&cantidadBloques, sizeof(cantidadBloques));
		archivo.read((char*)&this->tamanioBloque,sizeof(this->tamanioBloque)); //El segundo dato es el tamanio de cada registro.

    }
   // printf("sizeof bloque es %d \n",sizeof(Bloque));

    nombreArchivo = (string)nombre;

    leerMapaBits();


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

void ArchivoBloque::leerMapaBits(){

        string dirMapaBits = nombreArchivo + "MapaBits";
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

void ArchivoBloque::escribirEspaciosLibres(){

        string dirMapaBits = nombreArchivo + "MapaBits";
        ofstream archivoMapaBits;
        archivoMapaBits.open(dirMapaBits.c_str(), fstream::binary);
        archivoMapaBits.seekp(0, ios::beg);
        for(unsigned int i=0; i< vectorMapaBits.size(); i++)
                archivoMapaBits.write((char*)&vectorMapaBits[i], sizeof(char));

        archivoMapaBits.close();
}

void ArchivoBloque::escribir(list<Atributo>* datosAtributos,list<tamanioYTipoAtributo>* listaTipoAtributos){

	Bloque* bloque = new Bloque(this->tamanioBloque);
	list<Atributo>::iterator it2 = datosAtributos->begin();

	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
		Atributo* atributo = new Atributo();
		if (it->tipo == TEXTO) {
			atributo->texto = it2->texto;
			bloque->agregarAtributo(atributo);

			//this->archivo.write(it2->texto,it->cantidadBytes);
		} else {
			cout<<it2->entero<<" "<<it->cantidadBytes<<endl;
			atributo->entero = it2->entero;
			bloque->agregarAtributo(atributo);
			//this->archivo.write((char*)&it2->entero,it->cantidadBytes);
		}
		it2++;
	}

		//if(bloque->getTamanio() > tamanioBloque) return -1; // ERROR DE TAMANIO OVERFLOW EN EL BLOQUE

        unsigned int posicion = this->siguientePosicionLibre();
        archivo.seekp(sizeof(cantidadBloques) + posicion*tamanioBloque, ios::beg);
        archivo.write((char*)bloque, sizeof(bloque));
        cantidadBloques++;

        //return posicion;
}

int ArchivoBloque::reescribir(Bloque* bloque, unsigned int posicion){

        if(bloque->getTamanio() > tamanioBloque) return -1; // ERROR
        if(posicion >= vectorMapaBits.size()) return -1 ;// ERRROR

        archivo.seekp(sizeof(cantidadBloques) + posicion*tamanioBloque, ios::beg);
        archivo.write((char*)bloque, tamanioBloque);
        return 1; // TERMINA BIEN
}

unsigned int ArchivoBloque::siguientePosicionLibre(){

        unsigned int pos;
        for(pos= 0; pos<vectorMapaBits.size() && vectorMapaBits.at(pos)=='1'; pos++){};
        if(pos== vectorMapaBits.size())
             vectorMapaBits.push_back('1');
        else vectorMapaBits.at(pos) = '1';

        return pos;
}

list<Atributo>* ArchivoBloque::leer(int numeroBloque, list<tamanioYTipoAtributo>* listaTipoAtributos){

	list<Atributo>* listaAtributos = new list<Atributo>;
	if (numeroBloque > this->cantidadBloques) return NULL; // O throw exception
	if (this->vectorMapaBits.at(numeroBloque) == '0') return NULL;

	this->archivo.seekg(sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + numeroBloque * this->tamanioBloque,ios::beg);

	for (list<tamanioYTipoAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
		Atributo aux;
		Bloque* bloque = new Bloque(this->tamanioBloque);

		if (it->tipo == TEXTO) {
			this->archivo.read((char*)&aux.texto,it->cantidadBytes);
		} else {
			this->archivo.read((char*)&aux.entero,it->cantidadBytes);
		}
		listaAtributos->push_back(aux);
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

int ArchivoBloque::borrar(unsigned int numBloque){

        if(numBloque >= vectorMapaBits.size()) return -1; // ERROR

        vectorMapaBits.at(numBloque) = '0' ;
        cantidadBloques--;
        return 1; // termina bien
}

