#include "Interfaz.h"

Interfaz::Interfaz(){
	this -> opciones = new list<string>;
	//this -> opciones -> push_back("Crear nueva Entidad.");
	this -> opciones -> push_back("Crear nueva Instancia.");
	this -> opciones -> push_back("Modificar Instancia.");
	this -> opciones -> push_back("Eliminar instancia.");
	this -> opciones -> push_back("Eliminar todas las instancias.");
	this -> opciones -> push_back("Listar instancias.");
	this->opciones->push_back("Administrar Indices Secundarios");
	this->opciones->push_back("Consultas");
	this -> opciones -> push_back("Salir.");
	this -> adminEntidades    = new AdministradorEntidades();
	this -> adminEntidades->leerArchivoEntidades(); // Inicializa administrador si existe archivo preexistente.
	this->adminIndices = new AdministradorIndices();
	this->consulta = new Consulta(this->adminEntidades);
}

Interfaz::~Interfaz(){
	delete this->opciones;
	delete this->adminEntidades;
	delete this->adminIndices;
	delete this->adminRegistros;
}

void Interfaz::listar_opciones(){
	cout << "Ingrese el número de la opcion seleccionada:\n";
	int cont = 1;
	list<string>::iterator it = this->opciones->begin();
	while(it != this->opciones->end()){
		cout << "	" << cont << ") " << *it++ << "\n";
		cont++;
	}
}

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
//
//void Interfaz::crear_entidad(){
//	cout << "Ingrese el nombre de la entidad: ";
//	string nombre_entidad;
//	getline(cin,nombre_entidad); //preferible getline antes que cin >> porque incluye espacios
//
//	if(this->admin->entidadExistente(nombre_entidad)){ // Verificar que no exista.
//		cout<<"Ya existe entidad con ese nombre"<<endl;
//		return;
//	}
//
//	int indice = 1;
//	int opget = 0;
//	char tamanio[5];
//	unsigned int tamanio_string;
//	list<metaDataAtributo>* atts = new list<metaDataAtributo>; // Lista con atributos de la entidad.
//	metaDataAtributo att;
//
//	/* Agrega el atributo del identificador
//	att.cantidadBytes = sizeof(int); att.tipo = ENTERO; att.nombre = "ID"; att.idEntidad = 0;
//	atts->push_back(att);
//
//	while(true){
//	/*    Pide atributos hasta que la opción de tipo de atributo sea      *
//	 *  diferente de las existentes, en ese caso deja de pedir atributos.
//
//		cout << "\n Atributo N°" << indice << ": \n  Tipo de atributo: \n";
//		cout << "    1. Entero.\n    2. Cadena de caracteres.\n    3. Entidad X."<<endl;
//		cout << "    0. Salir"<<endl;
//		opget = this -> pedir_opcion();
//
//		if( opget > 3 || opget < 1 ){break;} // Opción no válida.
//
//		// Agregar que hacer cuando no sea una opcion correcta.
//
//		switch(opget){
//		/* Tipo de atributo seleccionado
//
//			case 1: // Entero
//				att.cantidadBytes = sizeof(int); att.tipo = ENTERO;
//				att.idEntidad = 0;
//				break;
//
//			case 2: // Cadena de caracteres
//				cout << "Ingrese el tamaño de la cadena de caracteres: ";
//				cin >> tamanio;
//				cout << " \n";
//				cin.get();
//				tamanio_string = atoi(tamanio);
//				att.cantidadBytes = tamanio_string*sizeof(char); att.tipo = TEXTO;
//				att.idEntidad = 0;
//				cout << "\n";
//				break;
//
//			case 3: // Entidad X
//				att.cantidadBytes = sizeof(int); att.tipo = ENTID;	// Tamaño de la entidad, sizeof(int),
//																	// ya que guarda el ID de la entidad.
//
//				att.idEntidad = this->seleccionar_entidad();
//				break;
//		}
//
//		cout << "Ingrese el nombre del atributo: ";
//		std::string nombre_att;
//		do {
//			getline(cin,nombre_att);
//		} while (nombre_att.size() > 50);
//		//cin >> nombre_att;
//		cout << "\n";
//
//		att.nombre = nombre_att;
//		atts->push_back(att); // Agrega el atributo a la lista.
//		indice ++;
//	}
//
//	/*      Especificación de tipo de archivo
//	cout<<endl<<" Tipo de archivo para almacenar la entidad:"<<endl;
//	cout<<"    1. Archivo de registros de longitud fija."<<endl<<"    2. Archivo de registros de longitud variable."<<endl<<"    3. Archivo en bloque con registros de longitud variable."<<endl;
//	opget = this -> pedir_opcion();
//
//	if( opget > 3 || opget < 1 ){  // Opción no válida.
//		return;
//	}
//
//	TipoArchivo t_arch;
//
//	switch(opget){
//		/* Tipo de archivo seleccionado
//
//			case 1: // Archivo de registros de longitud fija.
//				 t_arch = FIJO;
//				break;
//
//			case 2: // Archivo de registros de longitud variable.
//				t_arch = VARIABLE;
//				break;
//
//			case 3: // Archivo en bloque con registros de longitud variable.
//				t_arch = DEBLOQUES;
//				break;
//	}
//
//	int id = this->admin->getUltimoID() + 1; // Pide ultimo id para asignarle a la entidad el siguiente
//
//	Entidad* ent = new Entidad(atts,nombre_entidad,id,t_arch);
//	this->admin->crearEntidad(ent);
//}

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
	adminEntidades->modificarInstancia(ent->getID(),id_instancia);
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

int Interfaz::elegirEntidad(){
	this->adminEntidades->listarEntidades();
	cout << "Elegir indice: ";
	int x; cin >> x;
	return x;
}
void Interfaz::administrar_indices_secundarios(){
	cout << "1 - Crear nuevo indice secundario" << endl;
	cout << "2 - Eliminar indice secundario existente" << endl;
	cout << "3 - Listar indices secundarios" << endl;
	cout << "0 - Salir" << endl;
	int opc; cin >> opc;
	switch (opc) {
		case 1 : {
			Entidad* ent = this->adminEntidades->getEntidad(this->elegirEntidad());
			this->adminIndices->crear_indice(ent);
			break;
		}
		case 2: this->adminIndices->eliminar_indice(this->elegirEntidad());
				break;
		case 3: this->adminIndices->listar_indices();
				break;
		default: break;
	}
}

void Interfaz::registrar_ingreso(){

	int idEntProd = 14;
	int idEntColor =  3;
	int idEntEstampa = 4;
	int idEntTintura = 12;

	int cant, precio, idProd, idColor, idEstampa, idTintura, precioUnitario;
	Fecha date;
	Entidad *producto, *estampa, *color, *tintura;
	Instancia *instProd, *instColor, *instEstampa;
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
	producto->listarOpcionesInstancias();
	cout<<" Opcion seleccionada: ";
	idProd = this->pedir_valor();
	cout<<endl;

	// AVERIGUA PRECIO UNITARIO DEL PRODUCTO
	instProd = producto->getInstancia(idProd, error);
	if(error){
		cout<<"Opcion incorrecta"<<endl;
		return; 									// Mejorar validacion.
	}
	list<Atributo>::iterator itP = instProd->getListaAtributos()->begin();
	for(unsigned int j = 1 ; j < 5 ;++j){
		if(j==2)nombreProd = (*itP).texto; // Guardo nombre del producto.
		++itP;
	}
	precioUnitario = (*itP).entero;


	// PEDIR COLOR
	color = this->adminEntidades->getEntidad(idEntColor);
	cout<<"Colores: "<<endl;
	color->listarOpcionesInstancias();
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
	estampa->listarOpcionesInstancias();
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
	int opc;
	Fecha date;

	cout<<"Productos en Stock:"<<endl;
	if(!this->adminRegistros->listarRegistrosConStock()){
		return;
	}else{
		cout<<"Opcion seleccionada: ";
		opc = this->pedir_valor();
		cout<<endl;

		if(!this->adminRegistros->opcionValida(opc)){
			cout<<"Opcion invalida."<<endl;
			return;										// Mejorar validacion.
		}

		cout<<"Indique la fecha\n Día: ";
		date.dia = this->pedir_valor();
		cout<<" Mes: ";
		date.mes = this->pedir_valor();
		cout<<" Año: ";
		date.anio = this->pedir_valor();
		this->adminRegistros->registrarEgreso(opc,date);
	}
}

void Interfaz::listarConsultas(){

	cout<<"1: Cantidad de productos por Fabricante"<<endl;
	cout<<"2: Cantidad de productos por Familia"<<endl;
	cout<<"3: Cantidad de productos por Producto"<<endl;
	cout<<"4: Cantidad de productos por Tintura"<<endl;
	cout<<"5: Listar productos por Fabricante"<<endl;
	cout<<"6: Listar productos por Familia"<<endl;
	cout<<"7: Listar productos por Producto"<<endl;
	cout<<"8: Listar productos por Tintura"<<endl;
	cout<<"9: Listar productos por Partes"<<endl;
	cout<<"10: Listado de Ventas por fecha"<<endl;
	cout<<"11: Listado de Stock (actual)"<<endl;
	cout<<"12: Salir"<<endl;
	int opc = this->pedir_valor();
	int IDInstancia;
	switch (opc) {
	case 1:
		cout<<"Ingresar ID del Fabricante"<<endl;
		IDInstancia = this->pedirIDInstancia(1);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorFabricante(IDInstancia);
		break;
	case 2:
		cout<<"Ingresar ID de la Familia"<<endl;
		IDInstancia = this->pedirIDInstancia(10);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorFamilia(IDInstancia);
		break;
	case 3:
		cout<<"Ingresar ID del Producto"<<endl;
		IDInstancia = this->pedirIDInstancia(14);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorProducto(IDInstancia);
		break;
	case 4:
		cout<<"Ingresar ID de la Tintura"<<endl;
		IDInstancia = this->pedirIDInstancia(12);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorTintura(IDInstancia);
		break;
	case 5:
		cout<<"Ingresar ID del Fabricante"<<endl;
		IDInstancia = this->pedirIDInstancia(1);
		if (IDInstancia != -1)	this->consulta->listarProductosPorFabricante(IDInstancia);
		break;
	case 6:
		cout<<"Ingresar ID de la Familia"<<endl;
		IDInstancia = this->pedirIDInstancia(10);
		if (IDInstancia != -1)	this->consulta->listarProductosPorFamilia(IDInstancia);
		break;
	case 7:
		cout<<"Ingresar ID del Producto"<<endl;
		IDInstancia = this->pedirIDInstancia(14);
		if (IDInstancia != -1)	this->consulta->listarProductosPorProducto(IDInstancia);
		break;
	case 8:
		cout<<"Ingresar ID de la Tintura"<<endl;
		IDInstancia = this->pedirIDInstancia(12);
		if (IDInstancia != -1)	this->consulta->listarProductosPorTintura(IDInstancia);
		break;
	case 9:
		cout<<"Ingresar ID de las Partes"<<endl;
		IDInstancia = this->pedirIDInstancia(13);
		if (IDInstancia != -1)	this->consulta->cantidadProductosPorFabricante(IDInstancia);
		break;
	case 10:
		cout<<"Ingresar Fecha"<<endl;
		this->consulta->listarVentasPorFecha();
		break;
	case 11:
		this->consulta->listarStock();
		break;
	case 12:
		break;
	default:
		cout<<"Opcion ingresada es incorrecta"<<endl;
		break;
	}
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

bool Interfaz::ejecutar_opcion(unsigned int opc){
	switch (opc){
//		/case 1:	// Crear nueva entidad.
//			this->crear_entidad();
//			break;
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
		case 7: this->listarConsultas();
			break;
		default:
			return false;
	}
	return true;
}
