/*
 * Consultas.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: fran
 */

#include "Consultas.h"


Consulta::Consulta(AdministradorEntidades* admin) {
	this->admin = admin;
}


void Consulta::listarProductosPorFabricante(int IDFabricante){
	Entidad* entProducto = this->admin->getEntidad(14);
	Entidad* entFamilia = this->admin->getEntidad(10);
	for (int i = 1; i < entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* atrFamilia = producto->getAtributo(3); //Familia es el 3er atributo
			bool error2;
			Instancia* familia = entFamilia->getInstancia(atrFamilia->entero,error2);
			if (!error2) {
				Atributo* atrFabricante = familia->getAtributo(3);
				if (atrFabricante->entero == IDFabricante) {
					producto->imprimir();
				}
			}
		}
	}
}
