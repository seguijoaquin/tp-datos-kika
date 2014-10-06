/*
 * Bloque.cpp
 *
 *  Created on: 05/10/2014
 *      Author: juanmahidalgo
 */

#include "Bloque.h"

Bloque::Bloque(int tamaniodelbloque) {
	this->tamanio = tamaniodelbloque;
	this->cantInstancias = 0;
	this->espacioLibre = tamaniodelbloque;
}

Bloque::~Bloque() {
}

int Bloque::getCantInstancias(){
	return this->cantInstancias;
}

int Bloque::getTamanio(){
	return tamanio;
}

int Bloque::getEspacioLibre(){
	return espacioLibre;
}

void Bloque::setCantInstancias(int cant){
	this->cantInstancias = cant;
}

void Bloque::setEspacioLibre(int cant){
	this->espacioLibre = cant;
}

void Bloque::incrementarInstancias(){
	this->cantInstancias++;
}
