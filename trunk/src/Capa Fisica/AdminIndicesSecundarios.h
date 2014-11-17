/*
 * AdminIndicesSecundarios.h
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */

#ifndef ADMININDICESSECUNDARIOS_H_
#define ADMININDICESSECUNDARIOS_H_

#include "../Capa Logica/ArbolBMas/ArbolBMas.h"


class AdministradorIndices {

private:
	list<ArbolBMas>* indices;

public:
	void listar_indices();
	void eliminar_indice(int x);
	void crear_indice();
};

#endif /* ADMININDICESSECUNDARIOS_H_ */
