/*
 * AdminIndicesSecundarios.h
 *
 *  Created on: 17/11/2014
 *      Author: joaquin
 */

#ifndef ADMININDICESSECUNDARIOS_H_
#define ADMININDICESSECUNDARIOS_H_

#include <list>
#include <cstdlib>
#include "../Capa Logica/ArbolBMas/ArbolBMas.h"
#include "../Capa Fisica/Entidad.h"
#include "../Capa Logica/HashExtensible/Hash.h"
#include "../constantes.h"

#define ARBOL 1
#define HASH  2
#define LARGO_CADENA 64

struct Indice{
	ArbolBMas* arbol;
	Hash* hash;
	string nombreEntidad;
	string nombreArchivo;
	int tipo;
	list<string>* nombresAtributos;
};

class AdministradorIndices {

private:
	list<Indice>* indices;
//	list<ArbolBMas>* arboles;
//	list<Hash>* hashes;
	FILE* indicesCreados;
	void inicializarIndices();
	void persistirIndice(Indice* indice);
	void actualizarIndices();

public:
	AdministradorIndices();
	~AdministradorIndices();
	int listar_indices();
	void eliminar_indice();
	void crear_indice(Entidad* entidad);
	void mostrar_indice(int x);

};

#endif /* ADMININDICESSECUNDARIOS_H_ */
