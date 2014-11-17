/*
 * Estructura.h
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */

#ifndef ESTRUCTURA_H_
#define ESTRUCTURA_H_

#include <iostream>
#include "string.h"

using namespace std;

enum tipoEstructura { ARBOL, HASH};

class Estructura {
private:
	string nombre;
	tipoEstructura tipo;
public:
	Estructura();
	~Estructura();
    string getNombre();
    tipoEstructura getTipoEstructura();
    void setTipoEstructura(tipoEstructura T);
    void setNombre(string nombre);

};


#endif /* ESTRUCTURA_H_ */
