#ifndef ADMIN_REGISTROS
#define ADMIN_REGISTROS

#include <cstdlib>
#include <iostream>
#include <list>
#include <sstream>
#include "AdministradorEntidades.h"

#define LARGO_CADENA 30

using namespace std;

struct Fecha{
	int dia;
	int mes;
	int anio;
};

struct RegistroEntrada{
	Fecha date;
	int precio, precioUnitario;
	int cantidad;
	int idProducto, idTintura;
	char *nombreProd, *nombreColor, *nombreEstampa;
};

struct RegistroSalida{
	Fecha date;
	int precio;
	int idProducto;
	int idTintura;
	int cantidad;
	char *nombreProd, *nombreColor, *nombreEstampa;
};

class AdministradorRegistros {
private:
	list<RegistroEntrada>* regsIn;
	list<RegistroSalida>*  regsOut;
	FILE *archivoIn;
	FILE *archivoOut;
	void persistirRegistroIn(RegistroEntrada regIn);
	void persistirRegistroOut(RegistroSalida regOut);
	void leerRegistrosIn();
	void leerRegistrosOut();
	void actualizarRegistrosEnArchivo();
public:
	AdministradorRegistros();
	~AdministradorRegistros();
	void registrarIngreso(Fecha fecha, int idP, int idT, int precio, int cant, int precioUnit,char* nombreProd, char* nombreColor, char* nombreEstampa);
	void registrarEgreso(int reg, Fecha fecha, int cantidad);
	bool listarRegistrosConStock();
	void listarVentas();
	bool opcionValidaIngreso(int opc);
	void listarEgresosFecha(Fecha fecha);
};

#endif
