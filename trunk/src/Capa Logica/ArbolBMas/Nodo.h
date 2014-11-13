/*
 * Nodo.h
 *
 *  Created on: 13/11/2014
 *      Author: joaquin
 */

#ifndef NODO_H_
#define NODO_H_

#include <iostream>
#include <fstream>
#include "../../Capa Fisica/Archivos/Bloques/Bloques.h"
#include "Clave.h"
#include "string.h"
#include "RegistroArbol.h"

using namespace std;

class Nodo {

private:
	unsigned int nivel;
	unsigned int cantidadDeElementos;
	unsigned int NumeroDeBloque;
	static unsigned int tamanioMaximoBloque;

public:
	Nodo();
	virtual ~Nodo();

	/*getters y setters*/
	unsigned int getCantidadDeElementos();
	unsigned int getNivel();
	unsigned int getNumeroDeBloque();
	void setNumeroDeBloque(unsigned int numeroDeBloque);
	void setNivel(unsigned int nivel);
	void setCantidadDeElementos(unsigned int cantidad);

	/*----------------*/


	static void hidratar(char* bloque);
	virtual void persistir(ArchivoBloque* &archivo);
	virtual int tamanioOcupado();
	virtual bool estaVacio();
	void incrementarNivel();
	void decrementarNivel();
    int getTamanioUnderflow();
    int getTamanioOverflow();
    virtual bool hayOverflow();
    virtual bool hayUnderflow();
    void incrementarCantidadDeElementos();
    void decrementarCantidadDeElementos();
    static Nodo* cargar(ArchivoBloque* archivo, unsigned int indice);


};

#endif /* NODO_H_ */
