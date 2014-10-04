#ifndef INSTANCIA
#define INSTANCIA

#include <iostream>
#include <list>
#include <string.h>

using namespace std;

struct Atributo{
	int entero;	//Si es una instancia se guarda el ID
	string texto;
};

class Instancia {
private:
	list<Atributo> listaAtributos;
public:
	Instancia();
	~Instancia();
	list<Atributo>* getListaAtributos()
};

#endif
