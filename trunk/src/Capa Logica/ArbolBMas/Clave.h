/*
 * Clave.h
 *
 *  Created on: 13/11/2014
 *      Author: joaquin
 */

#ifndef CLAVE_H_
#define CLAVE_H_


#include <iostream>
#include "string.h"
#include "../../Capa Fisica/Archivos/Bloques/Bloques.h"

#define TAMANIOCLAVE_DEFAULT 64

using namespace std;

class Clave {

private:

	string id;
	static unsigned int tamanioMaximoBloque;

public:

	Clave();
	Clave(string);
	virtual ~Clave();
	string getClave();
	int getTamanioClave();
	void setClave(string);

	int persistir (char*);
	int hidratar (char*);

};

#endif /* CLAVE_H_ */
