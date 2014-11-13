/*
 * Clave.cpp
 *
 *  Created on: 13/11/2014
 *      Author: joaquin
 */


#include "Clave.h"



Clave::Clave(){

}

unsigned int Clave::tamanioMaximoBloque;

Clave::Clave(string clave) {
	this->id = clave;
	this->tamanioMaximoBloque = TAMANIOCLAVE_DEFAULT;
}

Clave::~Clave() {
}

string Clave::getClave(){

	return this->id;
}

int Clave::getTamanioClave() {

	return strlen(id.c_str()) +1;
}

void Clave::setClave(string clave){

	this->id = clave;

}


int Clave::persistir(char* bloque){

	//Devuelve la cantidad de bytes almacenados
	unsigned int bytesAlmacenados = 0;
	unsigned int tamanioClave = getTamanioClave();
	unsigned int tamanioInt = sizeof(unsigned int);

	//Agrego el tamanio de la clave
	memcpy(bloque, (char*)&tamanioClave, tamanioInt);
	bytesAlmacenados += tamanioInt;
	//Agrego la clave
	memcpy(bloque + bytesAlmacenados, id.c_str(), tamanioClave);
	bytesAlmacenados += tamanioClave;

	return bytesAlmacenados;

}

int Clave::hidratar(char* bloque){

	//Devuelve la cantidad de bytes hidratados
	int bytesLeidos = 0;
	unsigned int tamanioInt = sizeof(unsigned int);
	unsigned int tamanioClave;

	memcpy((char*)&tamanioClave, bloque, tamanioInt);
	bytesLeidos += tamanioInt;

	char bloqueAux[tamanioClave];
	memcpy(bloqueAux, bloque + tamanioInt, tamanioClave);
	bytesLeidos += tamanioClave;

	string clave(bloqueAux);
	//Seteo la clave nueva
	this->setClave(clave);

	return bytesLeidos;

}



