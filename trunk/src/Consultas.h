/*
 * Consultas.h
 *
 *  Created on: Nov 18, 2014
 *      Author: fran
 */

#ifndef CONSULTAS_H_
#define CONSULTAS_H_

#include "Capa Fisica/AdministradorEntidades.h"

using namespace std;

class Consulta {

	private:
		AdministradorEntidades* admin;
	public:
		Consulta(AdministradorEntidades* admin);
		void listarProductosPorFabricante(int IDFabricante);

};


#endif /* CONSULTAS_H_ */
