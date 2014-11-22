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

#define ARBOL 1
#define HASH  2

struct Indice{
	ArbolBMas* arbol;
	Hash* hash;
	string nombreEntidad;
	string nombreArchivo;
	int tipo;
	list<metaDataAtributo>* atributos;
};

class AdministradorIndices {

private:
	list<Indice>* indices;
//	list<ArbolBMas>* arboles;
//	list<Hash>* hashes;
	FILE* indicesCreados;
	void inicializarIndices();
	void persistirIndice(Indice* indice);

public:
	AdministradorIndices();
	~AdministradorIndices();
	void listar_indices();
	void eliminar_indice(int x);
	void crear_indice(Entidad* entidad);

};

#endif /* ADMININDICESSECUNDARIOS_H_ */
