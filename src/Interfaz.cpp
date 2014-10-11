#include "Interfaz.h"

Interfaz::Interfaz(){
	this -> opciones = new list<string>;
	this -> opciones -> push_back("Crear nueva Entidad.");
	this -> opciones -> push_back("Crear nueva Instancia.");
	this -> opciones -> push_back("Modificar Instancia.");
	this -> opciones -> push_back("Eliminar instancia.");
	this -> opciones -> push_back("Eliminar todas las instancias.");
	this -> opciones -> push_back("Listar instancias.");
	this -> opciones -> push_back("Salir.");
	this -> admin    = new AdministradorEntidades();
	this -> admin->leerArchivoEntidades(); // Inicializa administrador si existe archivo preexistente.
}

Interfaz::~Interfaz(){
	delete this->opciones;
	delete this->admin;
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

unsigned int Interfaz::pedir_opcion(){
	char opget[5];
	cout << "Ingrese la opcion seleccionada: ";
	cin >> opget;
	cout << " \n";
	cin.get();
	return atoi(opget);
}

int Interfaz::seleccionar_entidad(){
	cout<<" Entidades:"<<endl;
	this->admin->listarEntidades();
	unsigned int opc = this->pedir_opcion();
	return this->admin->getID(opc);
}

void Interfaz::crear_entidad(){
	cout << "Ingrese el nombre de la entidad: ";
	string nombre_entidad;
	getline(cin,nombre_entidad); //preferible getline antes que cin >> porque incluye espacios

	if(this->admin->entidadExistente(nombre_entidad)){ // Verificar que no exista.
		cout<<"Ya existe entidad con ese nombre"<<endl;
		return;
	}
	
	int indice = 1;
	int opget = 0;
	char tamanio[5];
	unsigned int tamanio_string;
	list<metaDataAtributo>* atts = new list<metaDataAtributo>; // Lista con atributos de la entidad.
	metaDataAtributo att;
	
	/* Agrega el atributo del identificador */
	att.cantidadBytes = sizeof(int); att.tipo = ENTERO; att.nombre = "ID";
	atts->push_back(att);
	
	while(true){
	/*    Pide atributos hasta que la opción de tipo de atributo sea      *
	 *  diferente de las existentes, en ese caso deja de pedir atributos. */
	 
		cout << "\n Atributo N°" << indice << ": \n  Tipo de atributo: \n";
		cout << "    1. Entero.\n    2. Cadena de caracteres.\n    3. Entidad X.\n";
		opget = this -> pedir_opcion();
		
		if( opget > 3 || opget < 1 ){break;} // Opción no válida.
		
		// Agregar que hacer cuando no sea una opcion correcta.
		
		switch(opget){
		/* Tipo de atributo seleccionado */
		
			case 1: // Entero
				att.cantidadBytes = sizeof(int); att.tipo = ENTERO;
				break;

			case 2: // Cadena de caracteres
				cout << "Ingrese el tamaño de la cadena de caracteres: ";
				cin >> tamanio;
				cout << " \n";
				cin.get();
				tamanio_string = atoi(tamanio);
				att.cantidadBytes = tamanio_string*sizeof(char); att.tipo = TEXTO;
				cout << "\n";
				break;

			case 3: // Entidad X
				att.cantidadBytes = sizeof(int); att.tipo = ENTID;	// Tamaño de la entidad, sizeof(int),
																	// ya que guarda el ID de la entidad.

				att.idEntidad = this->seleccionar_entidad();
				break;
		}
		
		cout << "Ingrese el nombre del atributo: ";
		char nombre_att[50];
		cin >> nombre_att;
		cout << "\n";

		att.nombre = nombre_att;
		atts->push_back(att); // Agrega el atributo a la lista.
		indice ++;
	}
	
	/*      Especificación de tipo de archivo      */
	cout<<endl<<" Tipo de archivo para almacenar la entidad:"<<endl;
	cout<<"    1. Archivo de registros de longitud fija."<<endl<<"    2. Archivo de registros de longitud variable."<<endl<<"    3. Archivo en bloque con registros de longitud variable."<<endl;
	opget = this -> pedir_opcion();
	
	if( opget > 3 || opget < 1 ){  // Opción no válida.
		return;
	}
	
	TipoArchivo t_arch;
	
	switch(opget){
		/* Tipo de archivo seleccionado */
		
			case 1: // Archivo de registros de longitud fija.
				 t_arch = FIJO;
				break;

			case 2: // Archivo de registros de longitud variable.
				t_arch = VARIABLE;
				break;

			case 3: // Archivo en bloque con registros de longitud variable.
				t_arch = DEBLOQUES;
				break;
	}
	
	int id = this->admin->getUltimoID() + 1; // Pide ultimo id para asignarle a la entidad el siguiente

	Entidad* ent = new Entidad(atts,nombre_entidad,id,t_arch);
	this->admin->crearEntidad(ent);
}

void Interfaz::crear_instancia(){
	int id = this->seleccionar_entidad();
	this->admin->crearInstancia(id);
}

void Interfaz::modificar_instancia(){

	int id_entidad = this->seleccionar_entidad();	// Preguntar el id de la entidad
	Entidad* ent = this->admin->getEntidad(id_entidad);	// Obtiene la entidad

	cout<<"Instancias de la entidad "<<ent->getNombre()<<":"<<endl;
	ent->listarInstancias();							// Muestra sus instancias.

	int id_instancia = this->pedir_opcion();	// Pide instancia a modificar.
	if (id_instancia > ent->getCantidadInstancias()){
		// Si la opcion obtenida es mayor a la cantidad de instancias.
		cout<<"Opción ingresada es incorrecta."<<endl;
		return;
	}
	ent->modificarInstancia(id_instancia);
}

void Interfaz::eliminar_instancia(){

	unsigned int id = this->seleccionar_entidad();
	Entidad* ent = this->admin->getEntidad(id);
	cout<<"Instancias de la entidad "<<ent->getNombre()<<":"<<endl<<endl;
	ent->listarInstancias();

	int num_instancia = this->pedir_opcion();	// Pide instancia a modificar.
	if (num_instancia > ent->getCantidadInstancias()){
		// Si la opcion obtenida es mayor a la cantidad de instancias.
		cout<<"Opción ingresada es incorrecta."<<endl;
		return;
	}
	this->admin->eliminarInstancia(id,num_instancia);
}

void Interfaz::eliminar_instancias(){
	int id = this->seleccionar_entidad();
	this->admin->eliminarInstancias(id);
}

void Interfaz::listar_instancias(){
	int id = this->seleccionar_entidad();
	this->admin->listarInstancias(id);
}

bool Interfaz::ejecutar_opcion(unsigned int opc){

	switch (opc){

		case 1:	// Crear nueva entidad.
			this->crear_entidad();
			break;

		case 2: // Crear nueva instancia.
			this->crear_instancia();
			break;

		case 3: // Modificar instancia.
			this->modificar_instancia();
			break;

		case 4: // Eliminar instancia.
			this->eliminar_instancia();
			break;

		case 5: // Eliminar todas las instancias.
			this->eliminar_instancias();
			break;

		case 6: // Listar instancias.
			this->listar_instancias();
			break;

		default:
			return false;
	}
	return true;
}
