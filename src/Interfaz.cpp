#include "Interfaz.h"

#include "Capa Fisica/AdministradorEntidades.h"

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
	this -> admin->leerArchivoEntidades();
	// Inicializar administrador por si existe archivo preexistente
}

Interfaz::~Interfaz(){
	delete this->opciones;
	delete this->admin;
}

void Interfaz::listar_opciones(){

	cout << "Ingrese el número de la opcion seleccionada:\n";
	int cont = 1;
	list<string>::iterator it = this->opciones->begin();
	while( it != this->opciones->end() )
	{
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

void Interfaz::crear_entidad(){
	cout << "Ingrese el nombre de la entidad: ";
	string nombre_entidad;
	getline(cin,nombre_entidad); //preferible getline antes que cin >> porque incluye espacios

	// Verificar que no exista.
	
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
				att.cantidadBytes = sizeof(int); att.tipo = ENTID; // Tamaño de la entidad, sizeof(int), 
																   // ya que guarda el ID de la entidad.
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
	this->admin->listarEntidades();
	unsigned int opc = this->pedir_opcion();
	int id = this->admin->getID(opc);
	this->admin->crearInstancia(id);
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
			cout << "Opcion 3."<<endl;
			break;
		case 4: // Eliminar instancia.
			cout<<"Opcion 4."<<endl;
			break;
		case 5: // Eliminar todas las instancias.
			cout<< "Opcion 5."<<endl;
			break;
		case 6: // Listar instancias.
			cout<<"Opcion 6."<<endl;
			break;
		default:
			return false;
	}
	return true;
}
