#include "AdministradorEntidades.h"

AdministradorEntidades::AdministradorEntidades(){
	this->archivo.open("entidades.txt",std::ios_base::out | std::ios_base::app);
	this->listaEntidades = new list<Entidad>;
}

AdministradorEntidades::~AdministradorEntidades(){
	this->archivo.close();
	this->listaEntidades->clear();
	delete this->listaEntidades;
}

void AdministradorEntidades::finalizarEntidad() {
	this->archivo << '\n';
}

void AdministradorEntidades::leerArchivoEntidades(){
/* parsea el archivo txt y carga la lista de entidades en memoria
 * */
}

void AdministradorEntidades::menuUsuario(){
	list<metaDataAtributo>* l1 = new list<metaDataAtributo>;
	metaDataAtributo t1;
	t1.cantidadBytes = sizeof(int); t1.tipo = ENTERO; t1.nombre = "ID";l1->push_back(t1);
	t1.cantidadBytes = sizeof(int); t1.tipo = TEXTO; t1.nombre = "Nombre";l1->push_back(t1);
	t1.cantidadBytes = sizeof(int); t1.tipo = ENTERO; t1.nombre = "Nro";l1->push_back(t1);
	Entidad* e1 = new Entidad(l1,"ent1",0,DEBLOQUES);
	e1->leerInstancias();
	//e1 tiene 2 enteros
	list<metaDataAtributo>* l2 = new list<metaDataAtributo>;
	t1.cantidadBytes = sizeof(int); t1.tipo = ENTERO; t1.nombre = "ID";l2->push_back(t1);
	t1.cantidadBytes = 20; t1.tipo = TEXTO; t1.nombre = "Nombre";l2->push_back(t1);
	//e2 es un entero y un string
	Entidad* e2 = new Entidad(l2,"ent2",0,FIJO);
	e2->leerInstancias();
	int opcion = 1;
	int n;
	do {
		cout<<"1 crea ent1, 2 crea ent2, 3 muestra ent1, 4 muestra ent2,5 eliminar de ent1, 6 eliminar de ent2"<<endl;

		cin >>opcion;
		switch (opcion){
			case 1:
				e1->crearInstancia();
				break;
			case 2:
				e2->crearInstancia();
				break;
			case 3:
				e1->listarInstancias();
				break;
			case 4:
				e2->listarInstancias();
				break;
			case 5:
				cout<<"Ingrese registro a eliminar(max "<<e1->getCantidad()<<" :";
				cin>>n;
				e1->borrar(n);
				break;
			case 6:
				cout<<"Ingrese registro a eliminar(max "<<e2->getCantidad()<<" :";
				cin>>n;
				e2->borrar(n);
				break;
		}
	} while (opcion > 0 && opcion < 7);
	delete e1;
	delete e2;
}

void AdministradorEntidades::agregarDato(string buffer) {
	this->archivo << buffer;
	this->archivo << '@';
}

void AdministradorEntidades::agregarDato(int buffer) {
	this->archivo << buffer;
	this->archivo << '@';
}

int AdministradorEntidades::getUltimoID() {
	return this->listaEntidades->end()->getID();
}

void AdministradorEntidades::crearEntidad(Entidad* entidad){
	//Agrego ID
	if (this->listaEntidades->size() == 0) { //Si la lista no tiene elementos, el primer ID es 1
		this->agregarDato(1);
	} else {
		this->agregarDato(listaEntidades->end()->getID()+1);
	}

	//Agrego Nombre
	cout << "Nombre Entidad:";
	string nombreEntidad;
	cin >> nombreEntidad;

	//Verificar si la entrada por teclado ya esta en el archivo
	this->agregarDato(nombreEntidad);

	//Agrego Tipo de Archivo
	cout << endl << "Agregar tipo de archivo: " <<
		 endl << "1 - De registros de longitud fija" <<
		 endl << "2 - De registros de longitud variable" <<
		 endl << "3 - De bloques con registros de longitud variable" <<
		 endl;
	int tipoArchivo;
	cin >> tipoArchivo;
	this->agregarDato(tipoArchivo);

	//AgregoAtributo
	cout << "Agregar atributo? (s/n)" << endl;
	char buffer;
	int opcionEntidad;
	cin >> buffer;
	while (buffer != 'n' ) {
		cout << "Tipo del atributo: " << endl;
		this->listarEntidades();
		cout << "#";
		cin >> opcionEntidad;

		//agarrar la entidad en la posicion 'opcionEntidad' de la lista y meterla en el archivo
		list<Entidad>::iterator it = listaEntidades->begin();
		string tipoAtributo;
		for(int i = 1 ; i < opcionEntidad ;++i) {
			++it;
		}
		tipoAtributo = it->getNombre();
		this->agregarDato(tipoAtributo);

		cout << "Nombre atributo: ";
		string nombreAtributo;
		cin >> nombreAtributo;
		this->agregarDato(nombreAtributo);
		cout << "Agregar atributo? (s/n)" << endl;
		cin >> buffer;
	}
	this->finalizarEntidad();
	//agregarEntidad a memoria
}

void AdministradorEntidades::listarEntidades() {
	list<Entidad>::iterator it = this->listaEntidades->begin();
	int cont = 1;
	while( it != this->listaEntidades->end() )
	{
		cout << cont << it->getNombre() << endl;
		++cont;
		++it;
	}
	cout << "------------------" << endl;
}

int AdministradorEntidades::getID(int x) {
	list<Entidad>::iterator it = listaEntidades->begin();
	string tipoAtributo;
	for(int i = 1 ; i < x ;++i) {
		++it;
	}
	return it->getID();
}

void AdministradorEntidades::crearInstancia(){

}

void AdministradorEntidades::modificarInstancia(){

}
