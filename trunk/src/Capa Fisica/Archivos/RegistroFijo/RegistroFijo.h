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
private:
	int cantRegistros;
	int tamanioRegistros;
	int proximoEspacioLibre();
};

#endif
