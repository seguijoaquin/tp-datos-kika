#include "AdministradorRegistros.h"

AdministradorRegistros::AdministradorRegistros(){
	this->regsIn = new list<RegistroEntrada>;
	this->regsOut = new list<RegistroSalida>;
	this->archivoIn = fopen("registrosIn.txt","r+b");
	if(!this->archivoIn)this->archivoIn = fopen("registrosIn.txt","w+");
	this->archivoOut = fopen("registrosOut.txt","r+b");
	if(!this->archivoOut)this->archivoOut = fopen("registrosOut.txt","w+");
	this->leerRegistrosIn();
	this->leerRegistrosOut();
}

AdministradorRegistros::~AdministradorRegistros(){
	this->actualizarRegistrosEnArchivo(); // Para actualizar stock de productos.
	delete this->regsIn;
	delete this->regsOut;
	fclose(this->archivoIn);
	fclose(this->archivoOut);
}

void AdministradorRegistros::actualizarRegistrosEnArchivo(){
	fclose(this->archivoIn);
	this->archivoIn = fopen("registrosIn.txt","w+");
	if (!this->regsIn->empty()) {
		list<RegistroEntrada>::iterator it = this->regsIn->begin();
		while(it != this->regsIn->end()){
			this->persistirRegistroIn(*it);
			++it;
		}
	}
}

void AdministradorRegistros::persistirRegistroIn(RegistroEntrada regIn){
	// date precio precioUnitario cantidad idProducto idTintura *nombreProd *nombreColor *nombreEstampa.
	fprintf(this->archivoIn,"%d %d %d ",regIn.date.dia,regIn.date.mes,regIn.date.anio);
	fprintf(this->archivoIn,"%d %d %d ",regIn.precio,regIn.precioUnitario,regIn.cantidad);
	fprintf(this->archivoIn,"%d %d ",regIn.idProducto,regIn.idTintura);
	fprintf(this->archivoIn,"%s %s %s\n",regIn.nombreProd,regIn.nombreColor,regIn.nombreEstampa);
}

void AdministradorRegistros::persistirRegistroOut(RegistroSalida regOut){
	// date precio cantidad idProducto idTintura *nombreProd *nombreColor *nombreEstampa.
	fprintf(this->archivoOut,"%d %d %d ",regOut.date.dia,regOut.date.mes,regOut.date.anio);
	fprintf(this->archivoOut,"%d ",regOut.precio);
	fprintf(this->archivoOut,"%d ",regOut.cantidad);
	fprintf(this->archivoOut,"%d %d ",regOut.idProducto,regOut.idTintura);
	fprintf(this->archivoOut,"%s %s %s\n",regOut.nombreProd,regOut.nombreColor,regOut.nombreEstampa);
}

void mostrarRegistro(RegistroEntrada r){
	cout<<"  Producto: "<<r.nombreProd<<endl;
	cout<<"  Color: "<<r.nombreColor<<endl;
	cout<<"  Estampa: "<<r.nombreEstampa<<endl;
	cout<<"  Fecha: "<<r.date.dia<<"/"<<r.date.mes<<"/"<<r.date.anio<<endl;
	cout<<"  Precio: "<<r.precio<<endl;
	cout<<"  Precio Unitario: "<<r.precioUnitario<<endl;
	cout<<"  Cantidad: "<<r.cantidad<<endl;
	cout<<"  ID Prod: "<<r.idProducto<<endl;
	cout<<"  ID Tint: "<<r.idTintura<<endl;
}

void AdministradorRegistros::leerRegistrosIn(){
	RegistroEntrada *regIn = new RegistroEntrada();
	Fecha *fecha = new Fecha();
	rewind (this->archivoIn);
	char producto[LARGO_CADENA];
	char color[LARGO_CADENA];
	char estampa[LARGO_CADENA];
	while(fscanf(this->archivoIn,"%d",&(fecha->dia)) != EOF){
		fscanf(this->archivoIn,"%d %d",&(fecha->mes),&(fecha->anio));
		regIn->date = *fecha;

		fscanf(this->archivoIn,"%d %d %d",&(regIn->precio),&(regIn->precioUnitario),&(regIn->cantidad));
		fscanf(this->archivoIn,"%d %d",&(regIn->idProducto),&(regIn->idTintura));

		fscanf(this->archivoIn,"%s",producto);
		regIn->nombreProd = (char*)malloc(LARGO_CADENA*sizeof(int));
		strcpy(regIn->nombreProd, producto);

		fscanf(this->archivoIn,"%s",color);
		regIn->nombreColor = (char*)malloc(LARGO_CADENA*sizeof(int));
		strcpy(regIn->nombreColor, color);

		fscanf(this->archivoIn,"%s",estampa);
		regIn->nombreEstampa = (char*)malloc(LARGO_CADENA*sizeof(int));
		strcpy(regIn->nombreEstampa, estampa);

		this->regsIn->push_back(*regIn);
		fecha = new Fecha();
		regIn = new RegistroEntrada();
	}
}

void AdministradorRegistros::leerRegistrosOut(){
	RegistroSalida *regOut = new RegistroSalida();
	Fecha *fecha = new Fecha();
	char producto[LARGO_CADENA];
	char color[LARGO_CADENA];
	char estampa[LARGO_CADENA];
	rewind (this->archivoOut);
	while(fscanf(this->archivoOut,"%d",&(fecha->dia)) != EOF){
		fscanf(this->archivoOut,"%d %d",&(fecha->mes),&(fecha->anio));
		regOut->date = *fecha;
		fscanf(this->archivoOut,"%d %d",&(regOut->precio),&(regOut->cantidad));
		fscanf(this->archivoOut,"%d %d",&(regOut->idProducto),&(regOut->idTintura));

		fscanf(this->archivoOut,"%s",producto);
		regOut->nombreProd = (char*)malloc(LARGO_CADENA*sizeof(int));
		strcpy(regOut->nombreProd, producto);

		fscanf(this->archivoOut,"%s",color);
		regOut->nombreColor = (char*)malloc(LARGO_CADENA*sizeof(int));
		strcpy(regOut->nombreColor, color);

		fscanf(this->archivoOut,"%s",estampa);
		regOut->nombreEstampa = (char*)malloc(LARGO_CADENA*sizeof(int));
		strcpy(regOut->nombreEstampa, estampa);

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
}

void AdministradorRegistros::registrarEgreso(int reg, Fecha fecha, int cantidad){
	RegistroSalida regOut;
	list<RegistroEntrada>::iterator it = this->regsIn->begin();
	for(int j = 1 ; j < reg ;++j) {
		++it;
	}
	if(((*it).cantidad) < 1) return;

	if((*it).cantidad < cantidad){
		cantidad = (*it).cantidad;
	}
	regOut.cantidad = cantidad;
	(*it).cantidad = (*it).cantidad - cantidad;
	regOut.precio = cantidad * (*it).precioUnitario;
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
				cout<<" "<<i<<"). "<<"Producto:"<<(*it).nombreProd<<endl;
				cout<<"     Color:   "<<(*it).nombreColor<<endl;
				cout<<"     Estampa: "<<(*it).nombreEstampa<<endl;
				cout<<"     Cantidad: "<<(*it).cantidad<<endl;
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

void AdministradorRegistros::listarVentas(){
	if (this->regsOut->empty()) {
		cout << "No se han realizado ventas" << endl;
	} else {
		list<RegistroSalida>::iterator it = this->regsOut->begin();
		int i = 1;
		while(it != this->regsOut->end()){
			cout<<" "<<i<<"). "<<"Producto:"<<(*it).nombreProd<<endl;
			cout<<"     Color:   "<<(*it).nombreColor<<endl;
			cout<<"     Estampa: "<<(*it).nombreEstampa<<endl;
			cout<<"     Precio: "<<(*it).precio<<endl;
			cout<<"     Cantidad: "<<(*it).cantidad<<endl;
			++it;
			i++;
		}
	}
}

bool AdministradorRegistros::opcionValidaIngreso(int opc){
	return ((opc <= this->regsIn->size()) && (opc > 0));
}
