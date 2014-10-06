/*
 * Bloque.cpp
 *
 *  Created on: 05/10/2014
 *      Author: juanmahidalgo
 */

#include "Bloque.h"

Bloque::Bloque(int tamaniodelbloque) {
	this->tamanio = tamaniodelbloque;
	this->cantAtributos = 0;
	this->cantInstancias = 0;
}

Bloque::~Bloque() {
	// TODO Auto-generated destructor stub
}


void Bloque::agregarInstancia(Instancia* instancia){

	this->vectorInstancias.push_back(instancia);
	this->cantInstancias++;
}


void Bloque::agregarAtributo(Atributo* atributo){
	if(atributo->entero != NULL){
		this->vectorAtributos.push_back(atributo);
	}
	this->cantAtributos++;

}

int Bloque::getCantInstancias(){
	return this->vectorInstancias.size();
}



int Bloque::getCantAtributos(){
	return this->vectorAtributos.size();
}


int Bloque::getTamanio(){
	return tamanio;
}

