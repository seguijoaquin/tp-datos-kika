/*
 * Consultas.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: fran
 */

#include "Consultas.h"


Consulta::Consulta(AdministradorEntidades* admin, AdministradorRegistros* adminregistros) {
	this->admin = admin;
	this->adminreg = adminregistros;

}


void Consulta::listarProductosPorFabricante(int IDFabricante){
	Entidad* entProducto = this->admin->getEntidad(14);
	Entidad* entFamilia = this->admin->getEntidad(10);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
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

void Consulta::listarProductosPorFamilia(int IDFamilia) {
	Entidad* entProducto = this->admin->getEntidad(14);
	Entidad* entFamilia = this->admin->getEntidad(10);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* atrFamilia = producto->getAtributo(3); //Familia es el 3er atributo
			bool error2;
			Instancia* familia = entFamilia->getInstancia(atrFamilia->entero,error2);
			if (!error2) {
				Atributo* idFam = familia->getAtributo(1);
				if (idFam->entero == IDFamilia) {
					producto->imprimir();
				}
			}
		}
	}
}

void Consulta::listarProductosPorProducto(int IDProducto){
	Entidad* entProducto = this->admin->getEntidad(14);
	//Entidad* entFamilia = this->admin->getEntidad(10);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* idProd = producto->getAtributo(1); //ID es el 1er atributo
			//bool error2;
			//Instancia* familia = entFamilia->getInstancia(atrFamilia->entero,error2);
			//if (!error2) {
				//Atributo* idFam = familia->getAtributo(3);
				if (idProd->entero == IDProducto) {
					producto->imprimir();
				}
			}
		}
}


void Consulta::listarProductosPorTintura(int IDTintura){

	Entidad* entProducto = this->admin->getEntidad(14);
	Entidad* entTintura = this->admin->getEntidad(12);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* atrTintura = producto->getAtributo(7); //Tintura es el 7mo atributo
			bool error2;
			Instancia* tintura = entTintura->getInstancia(atrTintura->entero,error2);
			if (!error2) {
				Atributo* idTint = tintura->getAtributo(1);
				if (idTint->entero == IDTintura) {
					producto->imprimir();
				}
			}
		}
	}


}
void Consulta::listarProductosPorPartes(int IDPartes){
	Entidad* entProducto = this->admin->getEntidad(14);
	Entidad* entPartes = this->admin->getEntidad(13);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* atrPartes = producto->getAtributo(4); //Partes es el 4to atributo
			bool error2;
			Instancia* partes = entPartes->getInstancia(atrPartes->entero,error2);
			if (!error2) {
				Atributo* idPar = partes->getAtributo(1);
				if (idPar->entero == IDPartes) {
					producto->imprimir();
				}
			}
		}
	}

}
void Consulta::cantidadProductosPorFabricante(int IDFabricante){
	int contador=0;
	Entidad* entProducto = this->admin->getEntidad(14);
	Entidad* entFamilia = this->admin->getEntidad(10);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* atrFamilia = producto->getAtributo(3); //Familia es el 3er atributo
			bool error2;
			Instancia* familia = entFamilia->getInstancia(atrFamilia->entero,error2);
			if (!error2) {
				Atributo* atrFabricante = familia->getAtributo(3);
				if (atrFabricante->entero == IDFabricante) {
					contador++;
				}
			}
		}
	}
	printf("Cantidad de Productos del Fabricante %d es : %d \n", IDFabricante, contador);
}
void Consulta::cantidadProductosPorFamilia(int IDFamilia){
	int contador = 0;
	Entidad* entProducto = this->admin->getEntidad(14);
	Entidad* entFamilia = this->admin->getEntidad(10);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* atrFamilia = producto->getAtributo(3); //Familia es el 3er atributo
			bool error2;
			Instancia* familia = entFamilia->getInstancia(atrFamilia->entero,error2);
			if (!error2) {
				Atributo* idFam = familia->getAtributo(1);
				if (idFam->entero == IDFamilia) {
					contador++;
				}
			}
		}
	}
	printf("Cantidad de Productos de la Familia %d es : %d \n", IDFamilia, contador);

}
void Consulta::cantidadProductosPorProducto(int IDProducto){
	int contador=0;
	Entidad* entProducto = this->admin->getEntidad(14);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* idProd = producto->getAtributo(1); //ID es el 1er atributo

				if (idProd->entero == IDProducto) {
					contador++;
				}
			}
		}
	printf("Cantidad de Productos del Producto %d es : %d \n", IDProducto, contador);



}
void Consulta::cantidadProductosPorTintura(int IDTintura){
	int contador=0;

	Entidad* entProducto = this->admin->getEntidad(14);
	Entidad* entTintura = this->admin->getEntidad(12);
	for (int i = 1; i <= entProducto->getUltimoIDInstancia();i++) {
		bool error;
		Instancia* producto= entProducto->getInstancia(i,error);
		if (!error) {
			Atributo* atrTintura = producto->getAtributo(7); //Tintura es el 7mo atributo
			bool error2;
			Instancia* tintura = entTintura->getInstancia(atrTintura->entero,error2);
			if (!error2) {
				Atributo* idTint = tintura->getAtributo(1);
				if (idTint->entero == IDTintura) {
					contador++;
				}
			}
		}
	}
	printf("Cantidad de Productos de la Tintura %d es : %d \n", IDTintura, contador);

}

void Consulta::listarVentasPorFecha(Fecha fecha){
	this->adminreg->listarEgresosFecha(fecha);

}
void Consulta::listarStock(){
	this->adminreg->listarRegistrosConStock();

}
