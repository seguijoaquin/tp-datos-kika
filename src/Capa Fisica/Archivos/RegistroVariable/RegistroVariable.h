#ifndef ARCHIVO_REGISTRO_VARIABLE
#define ARCHIVO_REGISTRO_VARIABLE

#include "../Archivo.h"

using namespace std;

struct espacioInstancia{
	int inicio;
	int fin;
};

class ArchivoRegistroVariable: public Archivo {
private:

public:
	ArchivoRegistroVariable(string nombre);
	~ArchivoRegistroVariable();
	list<Atributo>* leer(int numero,list<metaDataAtributo>* listaTipoAtributos);
	void escribir(list<Atributo>* atributos, list<metaDataAtributo>* listaTipoAtributos);
	int borrar(int IDInstancia);
	int modificarInstancia(int ID, list<Atributo>* atributos, list<metaDataAtributo>* listaTipoAtributos);
	int getCantidad();

private:
	vector<espacioInstancia> vectorMapaBits; //el mapa indica la ubicacion de cada instancia
	int cantInstancias;
	int proximoEspacioLibre(int tamanioInstancia);
	void leerMapaBits();
	void escribirMapaBits();
	int buscar(int ID);
};

#endif
