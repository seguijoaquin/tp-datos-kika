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

void AdministradorEntidades::agregarAtributo(metaDataAtributo atributo) {
	this->archivo << atributo.nombre;
	this->archivo << ":";
	switch (atributo.tipo) {
			case ENTERO:	this->agregarDato("ENTERO");
							break;
			case TEXTO: 	this->agregarDato("TEXTO");
							break;
			case ENTID: this->agregarDato("ENTID");
							break;
			default:		this->agregarDato("DEFAULT");
							break;
		}
}

void AdministradorEntidades::crearEntidad(Entidad* entidad){
	//Agregar a la lista la entidad
	this->listaEntidades->push_back(*entidad);
	//Escribir en el archivo de entidades la entidad pedida
	this->agregarDato(entidad->getID());
	this->agregarDato(entidad->getNombre());
	switch (entidad->getTipoArchivo()) {
		case FIJO:		this->agregarDato("FIJO");
						break;
		case VARIABLE: 	this->agregarDato("VARIABLE");
						break;
		case DEBLOQUES: this->agregarDato("DEBLOQUES");
						break;
		default:		this->agregarDato("DEFAULT");
						break;
	}
	this->agregarDato(entidad->getListaAtributos()->size());
	list<metaDataAtributo>::iterator it = entidad->getListaAtributos()->begin();
	while (it != entidad->getListaAtributos()->end()) {
		this->agregarAtributo(*it);
		++it;
	}
	this->finalizarEntidad();
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
