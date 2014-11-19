#include "AdministradorRegistros.h"

AdministradorRegistros::AdministradorRegistros(){
	this->regsIn = new list<RegistroEntrada>;
	this->regsOut = new list<RegistroSalida>;
}

AdministradorRegistros::~AdministradorRegistros(){
	delete this->regsIn;
	delete this->regsOut;
}

void AdministradorRegistros::registrarIngreso(Fecha fecha, int idP, int idT, int precio, int cant, int precioUnit, char* nombreProd, char* nombreColor, char* nombreEstampa){
	RegistroEntrada in;
	in.cantidad   = cant;
	in.date       = fecha;
	in.idProducto = idP;
	in.idTintura  = idT;
	in.precio     = precio;
	in.precioUnitario = precioUnit;
	in.nombreProd = nombreProd;
	in.nombreColor = nombreColor;
	in.nombreEstampa = nombreEstampa;
	this->regsIn->push_front(in);
	return;
}

void AdministradorRegistros::registrarEgreso(int reg, Fecha fecha){
	RegistroSalida regOut;

	list<RegistroEntrada>::iterator it = this->regsIn->begin();
	for(int j = 1 ; j < reg ;++j) {
		++it;
	}
	if(((*it).cantidad) < 1) return;
	(*it).cantidad = (*it).cantidad -1;
	regOut.precio = (*it).precioUnitario;
	regOut.date = fecha;
	regOut.idProducto = (*it).idProducto;
	regOut.idTintura = (*it).idTintura;
	regOut.nombreProd = (*it).nombreProd;
	regOut.nombreColor = (*it).nombreColor;
	regOut.nombreEstampa = (*it).nombreEstampa;
	this->regsOut->push_back(regOut);
}



bool AdministradorRegistros::listarRegistrosConStock(){
	if (this->regsIn->empty()) {
		cout << "No hay productos en Stock" << endl;
		return false;
	} else {
		list<RegistroEntrada>::iterator it = this->regsIn->begin();
		int i = 1;
		int contStock = 0;
		while(it != this->regsIn->end()){
			if(it->cantidad > 0){
				contStock++;
				*it;
				cout<<" "<<i<<"). "<<"Producto:"<<(*it).nombreProd<<endl;
				cout<<"     Color:   "<<(*it).nombreColor<<endl;
				cout<<"     Estampa: "<<(*it).nombreEstampa<<endl;
			}
			++it;
			i++;
		}
		if(contStock < 1){
			cout << "No hay productos en Stock" << endl;
			return false;
		}
	}
	return true;
}

bool AdministradorRegistros::opcionValida(int opc){
	return ((opc <= this->regsIn->size()) && (opc > 0));
}
