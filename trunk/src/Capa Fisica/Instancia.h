#ifndef INSTANCIA
#define INSTANCIA

#include <iostream>
#include <list>
#include <string.h>
#include "Archivos/Archivo.h"

using namespace std;



class Instancia {
private:
	list<Atributo>* listaAtributos;
public:
	Instancia();
	~Instancia();
	list<Atributo>* getListaAtributos();
	void setListaAtributos(list<Atributo>* lista);
	int getID();
};

#endif
