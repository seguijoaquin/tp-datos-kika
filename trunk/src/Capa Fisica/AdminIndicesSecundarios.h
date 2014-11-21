/*
 * AdminIndicesSecundarios.h
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */

#ifndef ADMININDICESSECUNDARIOS_H_
#define ADMININDICESSECUNDARIOS_H_

#include "../Capa Logica/ArbolBMas/ArbolBMas.h"
#include "../Capa Fisica/Entidad.h"
#include "../Capa Logica/HashExtensible/Hash.h"


class AdministradorIndices {

private:
	list<ArbolBMas>* arboles;
	list<Hash>* hashes;


public:
	AdministradorIndices();
	~AdministradorIndices();
	void listar_indices();
	void eliminar_indice(int x);
	void crear_indice(Entidad* entidad);

};

#endif /* ADMININDICESSECUNDARIOS_H_ */
