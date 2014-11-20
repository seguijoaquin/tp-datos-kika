#include "AdministradorRegistros.h"

AdministradorRegistros::AdministradorRegistros(){
	this->regsIn = new list<RegistroEntrada>;
	this->regsOut = new list<RegistroSalida>;
	this->archivoIn = fopen("registrosIn.txt","w+");
	this->archivoOut = fopen("registrosOut.txt","w+");
	this->leerRegistrosIn();
	this->leerRegistrosOut();
}

AdministradorRegistros::~AdministradorRegistros(){
	delete this->regsIn;
	delete this->regsOut;
	fclose(this->archivoIn);
	fclose(this->archivoOut);
}

void AdministradorRegistros::persistirRegistroIn(RegistroEntrada regIn){
	// date precio precioUnitario cantidad idProducto idTintura *nombreProd *nombreColor *nombreEstampa.
	fprintf(this->archivoIn,"%d %d %d ",regIn.date.dia,regIn.date.mes,regIn.date.anio);
	fprintf(this->archivoIn,"%d %d %d ",regIn.precio,regIn.precioUnitario,regIn.cantidad);
	fprintf(this->archivoIn,"%d %d ",regIn.idProducto,regIn.idTintura);
	fprintf(this->archivoIn,"%s %s %s\n",regIn.nombreProd,regIn.nombreColor,regIn.nombreEstampa);
}

void AdministradorRegistros::persistirRegistroOut(RegistroSalida regOut){
	// date precio idProducto idTintura *nombreProd *nombreColor *nombreEstampa.
	fprintf(this->archivoOut,"%d %d %d ",regOut.date.dia,regOut.date.mes,regOut.date.anio);
	fprintf(this->archivoOut,"%d ",regOut.precio);
	fprintf(this->archivoOut,"%d %d ",regOut.idProducto,regOut.idTintura);
	fprintf(this->archivoOut,"%s %s %s\n",regOut.nombreProd,regOut.nombreColor,regOut.nombreEstampa);
}

void AdministradorRegistros::leerRegistrosIn(){
	RegistroEntrada *regIn = new RegistroEntrada();
	Fecha *fecha = new Fecha();
	rewind (this->archivoIn);
	while(fscanf(this->archivoIn,"%d",&(fecha->dia)) != EOF){
		fscanf(this->archivoIn,"%d %d",&(fecha->mes),&(fecha->anio));
		regIn->date = *fecha;
		fscanf(this->archivoIn,"%d %d %d",&(regIn->precio),&(regIn->precioUnitario),&(regIn->cantidad));
		fscanf(this->archivoIn,"%d %d",&(regIn->idProducto),&(regIn->idTintura));
		fscanf(this->archivoIn,"%s %s %s",regIn->nombreProd,regIn->nombreColor,regIn->nombreEstampa);
		this->regsIn->push_back(*regIn);
		fecha = new Fecha();
		regIn = new RegistroEntrada();
	}
}

void AdministradorRegistros::leerRegistrosOut(){
	RegistroSalida *regOut = new RegistroSalida();
	Fecha *fecha = new Fecha();
	rewind (this->archivoOut);
	while(fscanf(this->archivoOut,"%d",&(fecha->dia)) != EOF){
		fscanf(this->archivoOut,"%d %d",&(fecha->mes),&(fecha->anio));
		regOut->date = *fecha;
		fscanf(this->archivoOut,"%d",&(regOut->precio));
		fscanf(this->archivoOut,"%d %d",&(regOut->idProducto),&(regOut->idTintura));
		fscanf(this->archivoOut,"%s %s %s",regOut->nombreProd,regOut->nombreColor,regOut->nombreEstampa);
		this->regsOut->push_back(*regOut);
		fecha = new Fecha();
		regOut = new RegistroSalida();
	}
}

void AdministradorRegistros::registrarIngreso(Fecha fecha, int idP, int idT, int precio, int cant, int precioUnit, char* nombreProd, char* nombreColor, char* nombreEstampa){
	RegistroEntrada regIn;
	regIn.cantidad   = cant;
	regIn.date       = fecha;
	regIn.idProducto = idP;
	regIn.idTintura  = idT;
	regIn.precio     = precio;
	regIn.precioUnitario = precioUnit;
	regIn.nombreProd = nombreProd;
	regIn.nombreColor = nombreColor;
	regIn.nombreEstampa = nombreEstampa;
	this->regsIn->push_back(regIn);
	this->persistirRegistroIn(regIn);
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
	this->persistirRegistroOut(regOut);
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
		//Caso en el que hay registros pero no hay stock.
			cout << "No hay productos en Stock" << endl;
			return false;
		}
	}
	return true;
}

bool AdministradorRegistros::opcionValidaIngreso(int opc){
	return ((opc <= this->regsIn->size()) && (opc > 0));
}
