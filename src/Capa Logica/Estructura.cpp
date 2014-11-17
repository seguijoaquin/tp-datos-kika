/*
 * Estructura.cpp
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */


#include "Estructura.h"

Estructura::Estructura(){

}

Estructura::~Estructura(){

}

string Estructura::getNombre() {
	return this->nombre;
}

tipoEstructura Estructura::getTipoEstructura() {
	return this->tipo;
}

void Estructura::setTipoEstructura(tipoEstructura T) {
	this->tipo = T;
}

void Estructura::setNombre(string nombre){
	this->nombre = nombre;
}
