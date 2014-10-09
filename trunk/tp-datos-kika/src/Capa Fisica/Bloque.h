/*
 * Bloque.h
 *
 *  Created on: 05/10/2014
 *      Author: juanmahidalgo
 */

#ifndef BLOQUE_H_
#define BLOQUE_H_

#include <iostream>
#include <math.h>
#include <string.h>
#include "Archivos/Archivo.h"
#include "Instancia.h"


class Bloque {
public:
	Bloque(int tamaniodelbloque);
	virtual ~Bloque();
	int getCantInstancias();
	int getTamanio();
	int getEspacioLibre();
	void setEspacioLibre(int cant);
	void setCantInstancias(int cant);
	void incrementarInstancias();

private:
	int tamanio;
	int cantInstancias;
	int espacioLibre;

};

#endif /* BLOQUE_H_ */
