/*
 * Consultas.h
 *
 *  Created on: Nov 18, 2014
 *      Author: fran
 */

#ifndef CONSULTAS_H_
#define CONSULTAS_H_

#include "Capa Fisica/AdministradorEntidades.h"
#include "Capa Fisica/AdministradorRegistros.h"

using namespace std;

class Consulta {

	private:
		AdministradorEntidades* admin;
		AdministradorRegistros* adminreg;
	public:
		Consulta(AdministradorEntidades* admin, AdministradorRegistros* adminregistros);
		void listarProductosPorFabricante(int IDFabricante);
		void listarProductosPorFamilia(int IDFamilia);
		void listarProductosPorProducto(int IDProducto);
		void listarProductosPorTintura(int IDTintura);
		void listarProductosPorPartes(int IDPartes);
		void cantidadProductosPorFabricante(int IDFabricante);
		void cantidadProductosPorFamilia(int IDFamilia);
		void cantidadProductosPorProducto(int IDProducto);
		void cantidadProductosPorTintura(int IDTintura);
		void listarVentasPorFecha(Fecha fecha);
		void listarStock();

};

#endif /* CONSULTAS_H_ */
