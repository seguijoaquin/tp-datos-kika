#ifndef INSTANCIA
#define INSTANCIA

#include <iostream>
#include <list>
#include <string.h>
#include "Archivos/Archivo.h"
#include "StringUtil.h"
using namespace std;



class Instancia {
private:
	list<Atributo>* listaAtributos;
	list<metaDataAtributo>* listaMetaAtributos;
public:
	Instancia(list<metaDataAtributo>* listaMetaAtributos);
	~Instancia();
	list<Atributo>* getListaAtributos();
	Atributo* getAtributo(metaDataAtributo* atributo);
	void setListaAtributos(list<Atributo>* lista);
	void setListaMetaAtributos(list<metaDataAtributo>* listaMetaAtributos);
	int getID();
	string serializar();
	void desSerializar(string aDeserealizar);
};

#endif
