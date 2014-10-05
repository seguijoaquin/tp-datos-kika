#include "AdministradorEntidades.h"

AdministradorEntidades::AdministradorEntidades(){
	this->listaEntidades = new list<Entidad>;
}

AdministradorEntidades::~AdministradorEntidades(){

}

void AdministradorEntidades::leerArchivoEntidades(){

}

void AdministradorEntidades::menuUsuario(){
	list<tamanioYTipoAtributo>* l1 = new list<tamanioYTipoAtributo>;
	tamanioYTipoAtributo t1;
	t1.cantidadBytes = sizeof(int); t1.tipo = ENTERO; l1->push_back(t1);
	t1.cantidadBytes = sizeof(int); t1.tipo = ENTERO; l1->push_back(t1);
	Entidad* e1 = new Entidad(l1,"ent1",0,FIJO);
	e1->leerInstancias();
	//e1 tiene 2 enteros
	list<tamanioYTipoAtributo>* l2 = new list<tamanioYTipoAtributo>;
	t1.cantidadBytes = sizeof(int); t1.tipo = ENTERO; l2->push_back(t1);
	t1.cantidadBytes = 20; t1.tipo = TEXTO; l2->push_back(t1);
	//e2 es un entero y un string
	Entidad* e2 = new Entidad(l2,"ent2",0,FIJO);
	e2->leerInstancias();
	cout<<"1->crea instancia ent1, 2 crea instancia ent2, 3 muestra instancias ent1, 4 muestra instancias ent2"<<endl;
	int opcion; cin >>opcion;
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
	}
}

void AdministradorEntidades::crearEntidad(){

}

void AdministradorEntidades::crearInstancia(){

}

void AdministradorEntidades::modificarInstancia(){

}
