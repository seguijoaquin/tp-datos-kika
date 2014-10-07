#include "AdministradorEntidades.h"

AdministradorEntidades::AdministradorEntidades(){
	this->listaEntidades = new list<Entidad>;
}

AdministradorEntidades::~AdministradorEntidades(){

}

void AdministradorEntidades::leerArchivoEntidades(){

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

void AdministradorEntidades::crearEntidad(){

}

void AdministradorEntidades::crearInstancia(){

}

void AdministradorEntidades::modificarInstancia(){

}
