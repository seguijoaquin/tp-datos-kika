#include "Interfaz.h"

Interfaz::Interfaz(){
	this -> adminEntidades    = new AdministradorEntidades();
	this -> adminEntidades->leerArchivoEntidades(); // Inicializa administrador si existe archivo preexistente.
	this -> adminIndices = new AdministradorIndices();
	this -> adminRegistros = new AdministradorRegistros();
	this -> consulta = new Consulta(this->adminEntidades, this->adminRegistros);
}

Interfaz::~Interfaz(){
	delete this->adminEntidades;
	delete this->adminIndices;
	delete this->adminRegistros;
	delete this->consulta;
}

/*                  AUXILIARES                 */

unsigned int Interfaz::pedir_valor(){
	char opget[5];
	cin >> opget;
	cout << endl;
	cin.get();
	return atoi(opget);
}

unsigned int Interfaz::pedir_opcion(){
	cout << "Ingrese la opcion seleccionada: ";
	return this->pedir_valor();
}

int Interfaz::seleccionar_entidad(){
	cout<<" Entidades:"<<endl;
	this->adminEntidades->listarEntidades();
	unsigned int opc;
	do {
		opc = this->pedir_opcion();
		opc = this->adminEntidades->getID(opc);
		if (opc == 0) {
			cout<<"Opcion ingresada es incorrecta, ingrese valor nuevamente"<<endl;
		}
	} while (opc == 0);
	return opc;
}

int Interfaz::elegirEntidad(){
	this->adminEntidades->listarEntidades();
	cout << "Elegir indice: ";
	int x; cin >> x;
	return x;
}

int Interfaz::pedirIDInstancia(int IDEntidad){
	Entidad* entidad = this->adminEntidades->getEntidad(IDEntidad);
	int n = this->pedir_valor();
	bool error;
	entidad->getInstancia(n,error);
	if (error) {
		cout<<"ID ingresado incorrecto"<<endl;
		return -1;
	} else {
		return n;
	}
}

/*                     MENU                    */

bool Interfaz::listar_opciones_menu_principal(){
	cout << endl<<"MENU PRINCIPAL"<<endl;
	cout << "	1). Administrar Entidades"<<endl;
	cout << "	2). Administrar Stock"<<endl;
	cout << "	3). Consultas"<<endl;
	cout << "	4). Libro de quejas en linea"<<endl;
	cout << "	0). Salir"<<endl;
	int opc = this->pedir_opcion();
	system("clear");
	switch (opc) {
		case 1 :
			this->listar_opciones_administrar_entidades();
			break;
		case 2:
			this->listar_opciones_administrar_stock();
			break;
		case 3:
			this->listar_opciones_consultas();
			break;
		case 4:
			this->listar_opciones_libro_quejas();
			break;
		case 0:
			return false;
		default:
			cout << "Opcion incorrecta." << endl;
			break;
	}
	return true;
}

bool Interfaz::listar_opciones_administrar_entidades(){
	cout << "ADMINISTRACION DE ENTIDADES" << endl;
	cout << "	1). Agregar nueva instancia"<<endl;
	cout << "	2). Modificar instancia existente"<<endl;
	cout << "	3). Eliminar instancia exitente"<<endl;
	cout << "	4). Eliminar todas las instancias existentes"<<endl;
	cout << "	5). Listar instancias"<<endl;
	cout << "	6). Administrar indices secundarios"<<endl;
	cout << "	0). Salir"<<endl;
	cout << "Ingrese el número de la opcion seleccionada:";
	int opc = this->pedir_opcion();
	system("clear");
	switch (opc) {
		case 1: // Crear nueva instancia.
			this->crear_instancia();
			break;
		case 2: // Modificar instancia.
			this->modificar_instancia();
			break;
		case 3: // Eliminar instancia.
			this->eliminar_instancia();
			break;
		case 4: // Eliminar todas las instancias.
			this->eliminar_instancias();
			break;
		case 5: // Listar instancias.
			this->listar_instancias();
			break;
		case 6: //Crear indice secundario
			this->administrar_indices_secundarios();
			break;
		case 0:
			return true;
		default:
			cout << "Opcion incorrecta." << endl;
			return false;
	}
	return true;
}

void Interfaz::administrar_indices_secundarios(){
	Entidad* ent;
	cout << "ADMINISTRACION DE INDICES SECUNDARIOS" << endl;
	cout << "	1). Crear nuevo indice secundario" << endl;
	cout << "	2). Eliminar indice secundario existente" << endl;
	cout << "	3). Listar indices secundarios" << endl << endl;
	cout << "	0). Salir" << endl;
	cout << "Ingrese el número de la opcion seleccionada:";
	int opc = this->pedir_opcion();
	system("clear");
	switch (opc) {
		case 1:
			ent = this->adminEntidades->getEntidad(this->elegirEntidad());
			this->adminIndices->crear_indice(ent);
			break;
		case 2:
			this->adminIndices->eliminar_indice();
			break;
		case 3:
			this->adminIndices->listar_indices();
			cout << endl << "Elija el indice a listar ";
			int x; cin >> x;
			this->adminIndices->mostrar_indice(x);
			break;
		default:
			break;
	}
}

bool Interfaz::listar_opciones_administrar_stock(){
	cout << "ADMINISTRACION DE STOCK" << endl;
	cout << "	1). Registrar ingreso"<<endl;
	cout << "	2). Registrar venta"<<endl;
	cout << "	3). Listar stock"<<endl;
	cout << "	4). Listar ventas"<<endl;
	cout << "	0). Salir"<<endl;
	int opc = this->pedir_opcion();
	system("clear");
	switch (opc) {
		case 1:
			this->registrar_ingreso();
			break;
		case 2:
			this->registrar_egreso();
			break;
		case 3:
			this->adminRegistros->listarRegistrosConStock();
			break;
		case 4:
			this->adminRegistros->listarVentas();
			break;
		case 5:
			break;
		default:
			cout<<"Opcion incorrecta."<<endl;
			return false;
	}
	return true;
}

bool Interfaz::listar_opciones_consultas(){
	cout << "CONSULTAS" << endl;
	cout << "   1). Cantidad de productos por Fabricante"<<endl;
	cout << "   2). Cantidad de productos por Familia"<<endl;
	cout << "   3). Cantidad de productos por Producto"<<endl;
	cout << "   4). Cantidad de productos por Tintura"<<endl;
	cout << "   5). Listar productos por Fabricante"<<endl;
	cout << "   6). Listar productos por Familia"<<endl;
	cout << "   7). Listar productos por Producto"<<endl;
	cout << "   8). Listar productos por Tintura"<<endl;
	cout << "   9). Listar productos por Partes"<<endl;
	cout << "   10). Listado de Ventas por fecha"<<endl;
	cout << "   11). Listado de Stock (actual)"<<endl;
	cout << "   0). Salir"<<endl;
	int opc = this->pedir_opcion();
	system("clear");
	int IDInstancia;
	switch (opc) {
	case 1:
		cout<<"Ingresar ID del Fabricante:";
		IDInstancia = this->pedirIDInstancia(1);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorFabricante(IDInstancia);
		break;
	case 2:
		cout<<"Ingresar ID de la Familia:";
		IDInstancia = this->pedirIDInstancia(10);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorFamilia(IDInstancia);
		break;
	case 3:
		cout<<"Ingresar ID del Producto:";
		IDInstancia = this->pedirIDInstancia(14);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorProducto(IDInstancia);
		break;
	case 4:
		cout<<"Ingresar ID de la Tintura:";
		IDInstancia = this->pedirIDInstancia(12);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorTintura(IDInstancia);
		break;
	case 5:
		cout<<"Ingresar ID del Fabricante:";
		IDInstancia = this->pedirIDInstancia(1);
		if (IDInstancia != -1)	this->consulta->listarProductosPorFabricante(IDInstancia);
		break;
	case 6:
		cout<<"Ingresar ID de la Familia:";
		IDInstancia = this->pedirIDInstancia(10);
		if (IDInstancia != -1)	this->consulta->listarProductosPorFamilia(IDInstancia);
		break;
	case 7:
		cout<<"Ingresar ID del Producto:";
		IDInstancia = this->pedirIDInstancia(14);
		if (IDInstancia != -1)	this->consulta->listarProductosPorProducto(IDInstancia);
		break;
	case 8:
		cout<<"Ingresar ID de la Tintura:";
		IDInstancia = this->pedirIDInstancia(12);
		if (IDInstancia != -1)	this->consulta->listarProductosPorTintura(IDInstancia);
		break;
	case 9:
		cout<<"Ingresar ID de las Partes:";
		IDInstancia = this->pedirIDInstancia(13);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorFabricante(IDInstancia);
		break;
	case 10:
		Fecha fecha;
		cout<<"Ingresar Fecha"<<endl;
		cout<<"Indique día: ";
		fecha.dia = this->pedir_valor();
		cout<<" Mes: ";
		fecha.mes = this->pedir_valor();
		cout<<" Año: ";
		fecha.anio = this->pedir_valor();
		this->consulta->listarVentasPorFecha(fecha);
		break;
	case 11:
		this->consulta->listarStock();
		break;
	case 0:
		break;
	default:
		cout<<"Opcion incorrecta"<<endl;
		return false;
	}
	return true;
}

bool Interfaz::listar_opciones_libro_quejas(){
	cout<<"Coming soon"<<endl;
	return true;
}

/*         ADMINISTRACION DE ENTIDADES         */

void Interfaz::crear_instancia(){
	int id = this->seleccionar_entidad();
	this->adminEntidades->crearInstancia(id);
}

void Interfaz::modificar_instancia(){
	int id_entidad = this->seleccionar_entidad();	// Preguntar el id de la entidad
	Entidad* ent = this->adminEntidades->getEntidad(id_entidad);	// Obtiene la entidad
	cout<<"Instancias de la entidad "<<ent->getNombre()<<":"<<endl;
	ent->listarInstancias();							// Muestra sus instancias.
	int id_instancia = this->pedir_opcion();	// Pide instancia a modificar.
	Instancia* instanciaVieja = NULL;
	Instancia* instanciaNueva = NULL;
	adminEntidades->modificarInstancia(ent->getID(),id_instancia,&instanciaVieja,&instanciaNueva);
	adminIndices->actualizar(instanciaNueva,instanciaVieja,ent->getNombre());
}

void Interfaz::eliminar_instancia(){
	unsigned int id = this->seleccionar_entidad();
	Entidad* ent = this->adminEntidades->getEntidad(id);
	cout<<"Instancias de la entidad "<<ent->getNombre()<<":"<<endl<<endl;
	ent->listarInstancias();

	int num_instancia = this->pedir_opcion();	// Pide instancia a modificar.
	this->adminEntidades->eliminarInstancia(id,num_instancia);
}

void Interfaz::eliminar_instancias(){
	int id = this->seleccionar_entidad();
	this->adminEntidades->eliminarInstancias(id);
}

void Interfaz::listar_instancias(){
	int id = this->seleccionar_entidad();
	this->adminEntidades->listarInstancias(id);
}

/*            ADMINISTRACION DE STOCK          */

void Interfaz::registrar_ingreso(){

	int idEntProd = 14;
	int idEntColor =  3;
	int idEntEstampa = 4;
	int idEntTintura = 12;
	int idEntFamilia = 10;
	int idEntPrecio = 9;

	int cant, precio, idProd, idColor, idEstampa, idTintura, precioUnitario;
	int idPrecio;
	Fecha date;
	Entidad *producto, *estampa, *color, *tintura, *familia, *price;
	Instancia *instProd, *instColor, *instEstampa, *instPrecio;
	char *nombreProd, *nombreColor, *nombreEstampa;
	bool error;


	// PEDIR FECHA
	cout<<" Día: ";
	date.dia = this->pedir_valor();
	cout<<" Mes: ";
	date.mes = this->pedir_valor();
	cout<<" Año: ";
	date.anio = this->pedir_valor();


	// PEDIR PRODUCTO
	producto = this->adminEntidades->getEntidad(idEntProd);
	cout<<"Productos:"<<endl;
	producto->listarInstancias();//listarOpcionesInstancias();
	cout<<" Opcion seleccionada: ";
	idProd = this->pedir_valor();
	cout<<endl;

	familia = this->adminEntidades->getEntidad(idEntFamilia);
	price = this->adminEntidades->getEntidad(idEntPrecio);
	// AVERIGUA PRECIO UNITARIO DEL PRODUCTO
	instProd = producto->getInstancia(idProd, error);
	if(error){
		cout<<"Opcion incorrecta"<<endl;
		return; 									// Mejorar validacion.
	}
	nombreProd = instProd->getAtributo(2)->texto;
	Instancia* instFam = familia->getInstancia(instProd->getAtributo(3)->entero,error);
	if (error) {
		return; //No tendria q pasar pero por si acaso
	}
	instPrecio = price->getInstancia(instFam->getAtributo(4)->entero,error);
	precioUnitario = 0;
	if (!error) {
		precioUnitario = instPrecio->getAtributo(2)->entero;
	}
	instPrecio = price->getInstancia(instProd->getAtributo(5)->entero,error);
	if (!error) {
		precioUnitario += instPrecio->getAtributo(2)->entero;
	}
	/*list<Atributo>::iterator itP = instProd->getListaAtributos()->begin();
	list<Atributo>::iterator itF;
	for(unsigned int j = 1 ; j <= 5 ;j++){
		if(j==2)nombreProd = (*itP).texto; // Guardo nombre del producto.
		if(j==3){ // FAMILIA - Para pedir precio
			itF = familia->getInstancia((*itP).entero,error)->getListaAtributos()->begin();
			if(error){
				cout<<"Opcion incorrecta - Familia"<<endl;
				return;
			}
			for(unsigned int k = 1 ; k < 4 ;++k){
				++itF;
			}

			idPrecio = itF->entero;
			cout<<idPrecio<<endl;
			price =this->adminEntidades->getEntidad(idEntPrecio);
			instPrecio = price->getInstancia(idPrecio,error);
			if(error){
					cout<<"Opcion incorrecta"<<endl;
					return;
			}
			precioUnitario = instPrecio->getAtributo(idPrecio)->entero;

		}
		++itP;
	}
	idPrecio = (*itP).entero;
	price =this->adminEntidades->getEntidad(idEntPrecio);
	instPrecio = price->getInstancia(idPrecio,error);
	if(error){
			cout<<"Opcion incorrecta"<<endl;
			return;
	}
	precioUnitario += instPrecio->getAtributo(idPrecio)->entero;
*/

	// PEDIR COLOR
	color = this->adminEntidades->getEntidad(idEntColor);
	cout<<"Colores: "<<endl;
	color->listarInstancias();//listarOpcionesInstancias();
	cout<<" Opcion seleccionada: ";
	idColor = this->pedir_valor();
	instColor = color->getInstancia(idColor,error);
	if(error){
		cout<<"Opcion incorrecta."<<endl;
		return;									// Mejorar validacion.
	}
	list<Atributo>::iterator itC= instColor->getListaAtributos()->begin();			// Nombre del color
	itC++; // Pasa a apuntar al nombre.
	nombreColor = (*itC).texto;
	cout<<endl;


	// PEDIR ESTAMPA
	estampa = this->adminEntidades->getEntidad(idEntEstampa);
	cout<<"Estampas: "<<endl;
	estampa->listarInstancias();//listarOpcionesInstancias();
	cout<<" Opcion seleccionada: ";
	idEstampa = this->pedir_valor();
	instEstampa = estampa->getInstancia(idEstampa,error);
	if(error){
		cout<<"Opcion incorrecta."<<endl;
		return;									// Mejorar validacion.
	}
	list<Atributo>::iterator itE= instEstampa->getListaAtributos()->begin();			// Nombre de la estampa
	itE++; // Pasa a apuntar al nombre.
	nombreEstampa = (*itE).texto;
	cout<<endl;


	// CREAR INSTANCIA DE TINTURA CON COLOR Y ESTAMPA.
	Atributo att;
	list<Atributo>* atts = new list<Atributo>;
	tintura = this->adminEntidades->getEntidad(idEntTintura);
	// Atributo ID
	idTintura = tintura->getUltimoIDInstancia() + 1;
	att.entero = idTintura;
	atts->push_back(att);
	// Atributo Color
	att.entero = idColor;
	atts->push_back(att);
	// Atributo Estampa
	att.entero = idEstampa;
	atts->push_back(att);
	tintura->crearInstancia(atts);


	// PEDIR CANTIDAD
	cout<<" Cantidad: ";
	cant = this->pedir_valor();


	// PEDIR PRECIO
	cout<<" Precio: ";
	precio = this->pedir_valor();

	this->adminRegistros->registrarIngreso(date,idProd,idTintura,precio,cant,precioUnitario,nombreProd,nombreColor,nombreEstampa);
}

void Interfaz::registrar_egreso(){
	int opc, cant;
	Fecha date;

	cout<<"Productos en Stock:"<<endl;
	if(!this->adminRegistros->listarRegistrosConStock()){
		return;
	}else{
		cout<<"Opcion seleccionada: ";
		opc = this->pedir_valor();
		cout<<endl;

		if(!this->adminRegistros->opcionValidaIngreso(opc)){
			cout<<"Opcion invalida."<<endl;
			return;										// Mejorar validacion.
		}

		cout<<"Indique la fecha\n Día: ";
		date.dia = this->pedir_valor();
		cout<<" Mes: ";
		date.mes = this->pedir_valor();
		cout<<" Año: ";
		date.anio = this->pedir_valor();
		cout<<"Cantidad de productos comprados: ";
		cant = this->pedir_valor();
		this->adminRegistros->registrarEgreso(opc,date,cant);
	}
}
