#ifndef ARCHIVO_REGISTRO_FIJO
#define ARCHIVO_REGISTRO_FIJO

#include "../Archivo.h"

using namespace std;

class ArchivoRegistroFijo: public Archivo {
private:

public:
	ArchivoRegistroFijo(string nombre);
	~ArchivoRegistroFijo();
	list<Atributo>* leer(int numero,list<tamanioYTipoAtributo>* listaTipoAtributos);
	void escribir(list<Atributo>* atributos, list<tamanioYTipoAtributo>* listaTipoAtributos);
	void borrar(int numero);
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
