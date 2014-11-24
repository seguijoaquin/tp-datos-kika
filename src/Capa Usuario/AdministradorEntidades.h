#ifndef ADMIN_ENTIDADES
#define ADMIN_ENTIDADES

#include <iostream>
#include <list>
#include <sstream>
#include "../Capa Fisica/Entidad.h"
#include "../Capa Fisica/Archivos/Archivo.h"
#include <cstring>
#include <cstdlib>


using namespace std;

struct Eliminados{
	int idEntidad;
	vector<int>* idInstancias;
};

class AdministradorEntidades {
private:
	list<Entidad>* listaEntidades;
	int ultimoID;
	std::fstream archivo;
	void finalizarEntidad();
	void agregarDato(string buffer);
	void agregarDato(int buffer);
	void agregarAtributo(metaDataAtributo atributo);
	bool validarCreacionInstancia(Entidad* ent);
	bool validarIdCreacionInstancia(Entidad* ent,int id_instancia,string nombreAtributo);
	vector<Eliminados>* informarEliminacion(Entidad* ent,unsigned int id_instancia);
	vector<Eliminados>* eliminacionDirecta(Entidad* ent,int id_instancia);
	vector<Eliminados>* eliminacionIndirecta(Entidad* ent,int id_instancia);
	vector<Eliminados>* eliminacionInIndirecta(Entidad* ent,int id_instancia);
public:
	AdministradorEntidades();
	~AdministradorEntidades();
	void menuUsuario();
	void leerArchivoEntidades();
	//void crearEntidad(Entidad* entidad);
	Instancia* crearInstancia(int id);
	int getUltimoID();
	int getID(int x);
	void listarEntidades();
	void listarInstancias(int id);
	Entidad* getEntidad(int id);
	Instancia* eliminarInstancia(unsigned int id, unsigned int id_instancia);
	void modificarInstancia(unsigned int id, unsigned int id_instancia,Instancia** instanciaVieja, Instancia** instanciaNueva);
	void eliminarInstancias(int id);
	bool entidadExistente(string nombre);

};

#endif
