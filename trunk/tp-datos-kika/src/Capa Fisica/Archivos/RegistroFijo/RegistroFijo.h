#ifndef ARCHIVO_REGISTRO_FIJO
#define ARCHIVO_REGISTRO_FIJO

#include "../Archivo.h"

using namespace std;

class ArchivoRegistroFijo: public Archivo {
private:

public:
	ArchivoRegistroFijo(string nombre,int tamRegistro);
	~ArchivoRegistroFijo();
	list<Atributo>* leer(int numero,list<metaDataAtributo>* listaTipoAtributos);
	void escribir(list<Atributo>* atributos, list<metaDataAtributo>* listaTipoAtributos);
	int borrar(int IDInstancia);
	int getCantidad();


private:
	vector<char> vectorMapaBits;
	int cantRegistros;
	int tamanioRegistros;
	int proximoEspacioLibre();
	void leerMapaBits();
	void escribirMapaBits();
};

#endif
