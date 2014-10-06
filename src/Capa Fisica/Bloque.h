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
	void agregarInstancia(Instancia* instancia);
	void agregarAtributo(Atributo* atributo);
	int getCantInstancias();
	int getCantAtributos();
	int getTamanio();
	int getEspacioLibre();
	void setEspacioLibre(int cant);
	void setCantInstancias(int cant);
	void incrementarInstancias();




private:
	vector<Instancia*> vectorInstancias;
	vector<Atributo*> vectorAtributos;
	int tamanio;
	int cantInstancias;
	int cantAtributos;
	int espacioLibre;

};

#endif /* BLOQUE_H_ */
