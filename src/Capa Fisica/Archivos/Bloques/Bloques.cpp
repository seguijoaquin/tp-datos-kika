#include "Bloques.h"


ArchivoBloque::ArchivoBloque(string nombre, int tamanio) {
	this->tamanioBloque = tamanio;//maxInstanciasEnBloque * (tamanio + sizeof(int));	//tamanioInsancia + dato q guarda el tamanio
	this->bloqueActual = 0;
    string rutaTabla = "tabla.dat";
    std::size_t found = nombre.find(rutaTabla);
    if (found!=std::string::npos) {
    	this->tamanioBloque = 4;
    }
	archivo.open(nombre.c_str(), fstream::in | fstream::out | fstream::binary);
    if(!archivo){ // si no existe, crear archivo nuevo
        archivo.open(nombre.c_str(), fstream::in | fstream::out | fstream::binary | fstream::trunc);
        cantidadBloques=0;
    }else{
        archivo.seekg(0, ios::beg);
        archivo.read((char*)&cantidadBloques, sizeof(cantidadBloques));
    }
    nombreArchivo = nombre;

    leerMapaBloques();
}

ArchivoBloque::~ArchivoBloque() {
	escribirEspaciosLibres();
	archivo.seekp(0, ios::beg);
	archivo.write((char*)&cantidadBloques, sizeof(cantidadBloques));
	archivo.close();
}

void ArchivoBloque::leerMapaBloques(){

	string dirMapaBloques = nombreArchivo + "MapaBloques";

	ifstream archivoMapaBloques;
	archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary);
	if(!archivoMapaBloques) // si no existe, crear archivo nuevo
		archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary | fstream::app);

	char bit;
	archivoMapaBloques.read((char*)&bit, sizeof(char));
	while(!archivoMapaBloques.eof()){
		vectorMapaBits.push_back(bit);
		archivoMapaBloques.read((char*)&bit, sizeof(char));
	}

   /* ifstream archivoMapaBloques;
	archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary);
	if(!archivoMapaBloques) // si no existe, crear archivo nuevo
		archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary | fstream::app);

	int bloqueActual = 0;
	int cantInstanciasBloque;
	int espacioLibreBloque;
	archivoMapaBloques.read((char*)&cantInstanciasBloque, sizeof(cantInstanciasBloque));
	archivoMapaBloques.read((char*)&espacioLibreBloque, sizeof(espacioLibreBloque));
	while(!archivoMapaBloques.eof()){
		Bloque* bloque = new Bloque(this->tamanioBloque);
		bloque->setCantInstancias(cantInstanciasBloque);
		bloque->setEspacioLibre(espacioLibreBloque);
		this->vectorBloques.push_back(bloque);
		archivoMapaBloques.read((char*)&cantInstanciasBloque, sizeof(cantInstanciasBloque));
		archivoMapaBloques.read((char*)&espacioLibreBloque, sizeof(espacioLibreBloque));
		bloqueActual++;
	}
*/
	archivoMapaBloques.close();
}

void ArchivoBloque::escribirEspaciosLibres(){

        string dirMapaBloques = nombreArchivo + "MapaBloques";
        ofstream archivoMapaBloques;

        archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary);
        archivoMapaBloques.seekp(0, ios::beg);
    	for(unsigned int i=0; i< vectorMapaBits.size(); i++)
    		archivoMapaBloques.write((char*)&vectorMapaBits[i], sizeof(char));

       /* archivoMapaBloques.open(dirMapaBloques.c_str(), fstream::binary);
        archivoMapaBloques.seekp(0, ios::beg);

        for(unsigned int i=0; i< this->cantidadBloques; i++){
        	int cantInstancias = this->vectorBloques[i]->getCantInstancias();
        	int espacioLibre = this->vectorBloques[i]->getEspacioLibre();
        	archivoMapaBloques.write((char*)&cantInstancias, sizeof(this->vectorBloques[i]->getCantInstancias()));
        	archivoMapaBloques.write((char*)&espacioLibre, sizeof(this->vectorBloques[i]->getEspacioLibre()));
        }
*/
        archivoMapaBloques.close();
}

void ArchivoBloque::escribir(list<Atributo>* datosAtributos,list<metaDataAtributo>* listaTipoAtributos){

	int tamanioInstancia = sizeof(int);	//Se guarda tamanioInstancia en archivo
	list<Atributo>::iterator it2 = datosAtributos->begin();
	for (list<metaDataAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end();it++,it2++){
		if (it->tipo == TEXTO) {
			tamanioInstancia += strlen(it2->texto) + 1; //+1 por el caracter separador
		} else {
			tamanioInstancia += sizeof(it2->entero);
		}
	}

	int proximoEspacioLibre = this->siguientePosicionLibre(tamanioInstancia);
	this->archivo.seekp(proximoEspacioLibre,ios::beg);
	it2 = datosAtributos->begin();
	this->archivo.write((char*)&tamanioInstancia,sizeof(tamanioInstancia));
	for (list<metaDataAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++,it2++) {
		if (it->tipo == TEXTO) {
			this->archivo.write(it2->texto,strlen(it2->texto));
			this->archivo.write(&separadorString,1);
		} else {
			this->archivo.write((char*)&(it2->entero),it->cantidadBytes);
		}
	}
	this->vectorBloques[this->bloqueActual]->incrementarInstancias();
	this->vectorBloques[this->bloqueActual]->setEspacioLibre(this->vectorBloques[this->bloqueActual]->getEspacioLibre() - tamanioInstancia);
}

unsigned int ArchivoBloque::escribir(char* bloque){

	if(strlen(bloque) > tamanioBloque) throw ExcepcionOverflowTamBloque();
	unsigned int posicion = this->siguientePosicionLibre();
	archivo.seekp(sizeof(cantidadBloques) + posicion*tamanioBloque, ios::beg);
	archivo.write(bloque, tamanioBloque);
	cantidadBloques++;

	return posicion;
}

unsigned int ArchivoBloque::siguientePosicionLibre(){

	unsigned int pos;
	for(pos= 0; pos<vectorMapaBits.size() && vectorMapaBits.at(pos)=='1'; pos++){};
	if(pos== vectorMapaBits.size())
	     vectorMapaBits.push_back('1');
	else vectorMapaBits.at(pos) = '1';

	return pos;
}


unsigned int ArchivoBloque::siguientePosicionLibre(int tamanioInstancia){

	for (unsigned int i = 0; i < this->cantidadBloques; i++){
		Bloque* bloque = this->vectorBloques[i];
		if(bloque->getEspacioLibre() >= tamanioInstancia){
			this->bloqueActual = i;
			return (sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + (i * this->tamanioBloque) + (this->tamanioBloque - bloque->getEspacioLibre()));
		}
	}
	//Hay que crear bloque nuevo
	this->bloqueActual = cantidadBloques;
	this->cantidadBloques++;
	//Actualizo vectorBloques
	Bloque* bloque = new Bloque(this->tamanioBloque);
	bloque->setCantInstancias(0);
	this->vectorBloques.push_back(bloque);

	return (sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + this->bloqueActual * this->tamanioBloque);
}

list<Atributo>* ArchivoBloque::leer(int numeroBloque, list<metaDataAtributo>* listaTipoAtributos){

	list<Atributo>* listaAtributos = new list<Atributo>;
	if (numeroBloque > this->cantidadBloques) return NULL; // O throw exception
	if (this->vectorBloques[numeroBloque]->getCantInstancias() == 0) return NULL;

	this->archivo.seekg(sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + numeroBloque * this->tamanioBloque,ios::beg);
	for(int i = 0; i < this->vectorBloques[numeroBloque]->getCantInstancias(); i++) {
		int tamanio;
		this->archivo.read((char*)&tamanio,sizeof(tamanio));
		for (list<metaDataAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++) {
			Atributo aux;
			if (it->tipo == TEXTO) {
				char* buffer = new char[maxCantidadCaracteres + 1]; //+1 por separador
				int i = 0;
				this->archivo.read(&buffer[i],1);
				while (buffer[i] != separadorString && i < maxCantidadCaracteres) { //leo hasta encontrar caracter separador
					i++;
					this->archivo.read(&buffer[i],1);
				}
				if (buffer[i] == separadorString) {
					aux.texto = new char[i+1];
					strncpy(aux.texto,buffer,i);
					aux.texto[i] = NULL;
				} else {
					cout<<"Error leyendo"<<endl; //Hubo algun error
				}
			} else {
				this->archivo.read((char*)&aux.entero,it->cantidadBytes);
			}
			listaAtributos->push_back(aux);
		}
	}
	return listaAtributos;
}

void ArchivoBloque::leer(char* &bloque, unsigned int numBloque){

	archivo.seekg(sizeof(cantidadBloques) + numBloque*tamanioBloque, ios::beg);
	archivo.read(bloque, tamanioBloque);
}

void ArchivoBloque::reescribir(char* bloque, unsigned int posicion){

	if(strlen(bloque) > tamanioBloque) throw ExcepcionOverflowTamBloque();
	if(posicion >= this->vectorMapaBits.size()) throw ExcepcionBloqueInexistente();

	archivo.seekp(sizeof(cantidadBloques) + posicion*tamanioBloque, ios::beg);
	archivo.write(bloque, tamanioBloque);
}

unsigned int ArchivoBloque::getCantidadBloques(){
	return cantidadBloques;
}

int ArchivoBloque::getCantidad(){
	return cantidadBloques;
}

unsigned int ArchivoBloque::getTamanoBloque(){
	return tamanioBloque;
}

int ArchivoBloque::borrar(int numeroBloque){
	/*int pos = this->buscar(IDInstancia);
	if (pos != -1) {
		archivo.seekg(pos,ios::beg);
		int tamanio;
		archivo.read((char*)&tamanio,sizeof(tamanio));
		//sizeof(cantidadBloques) + sizeof(tamanioBloque) = 8
		int espacioACopiar = 8 + (bloqueActual + 1) * tamanioBloque - (pos + tamanio);
		char* buffer = new char[espacioACopiar];
		archivo.seekg(0,ios::end);
		if (pos + tamanio + espacioACopiar >= archivo.tellg()){
			espacioACopiar = archivo.tellg() - pos - tamanio;
		}
		archivo.seekg(pos + tamanio,ios::beg);
		archivo.read(buffer,espacioACopiar);

		archivo.seekp(pos,ios::beg);
		archivo.write(buffer,espacioACopiar);
		this->vectorBloques[bloqueActual]->setCantInstancias(this->vectorBloques[bloqueActual]->getCantInstancias() - 1);
		this->vectorBloques[bloqueActual]->setEspacioLibre(this->vectorBloques[bloqueActual]->getEspacioLibre() + tamanio);
		return 1;
	}
	return 0;*/
	if(numeroBloque >= vectorMapaBits.size()) throw ExcepcionBloqueInexistente();

	vectorMapaBits.at(numeroBloque) = '0' ;
	cantidadBloques--;
	return 0;
}

int ArchivoBloque::buscar(int IDInstancia){
	bool encontrado = false;
	int ID,tamanioInstancia,posActual;
	for (unsigned int i = 0; (i < this->cantidadBloques) && (!encontrado); i++) {
		this->archivo.seekg(sizeof(this->cantidadBloques) + sizeof(this->tamanioBloque) + i * this->tamanioBloque,ios::beg);
		for (int j = 0; (j < this->vectorBloques[i]->getCantInstancias()) && (!encontrado);j++) {
			posActual = this->archivo.tellg();
			this->archivo.read((char*)&tamanioInstancia,sizeof(tamanioInstancia));
			this->archivo.read((char*)&ID,sizeof(ID));
			if (ID == IDInstancia) {
				this->bloqueActual = i;
				return posActual;
			} else {
				this->archivo.seekg(posActual + tamanioInstancia,ios::beg);
			}
		}
	}
	return -1;
}

int ArchivoBloque::modificarInstancia(int ID, list<Atributo>* atributos, list<metaDataAtributo>* listaTipoAtributos){
	int pos = this->buscar(ID);
	if (pos != -1 ){

		int tamanioInstanciaNuevo = sizeof(int);	//Se guarda tamanioInstancia en archivo
		list<Atributo>::iterator it2 = atributos->begin();
		for (list<metaDataAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end();it++,it2++){
			if (it->tipo == TEXTO) {
				tamanioInstanciaNuevo += strlen(it2->texto) + 1; //+1 por el caracter separador
			} else {
				tamanioInstanciaNuevo += sizeof(it2->entero);
			}
		}
		int tamanioInstanciaViejo;
		this->archivo.seekg(pos,ios::beg);
		this->archivo.read((char*)&tamanioInstanciaViejo,sizeof(tamanioInstanciaViejo));
		if (tamanioInstanciaViejo < tamanioInstanciaNuevo ) { //Si no entra donde estaba
			this->borrar(ID);
			this->escribir(atributos,listaTipoAtributos);
		} else {	//Lo escribo donde estaba y muevo lo q estaba despues para atras.
			//Escribo
			this->archivo.seekp(pos,ios::beg);
			it2 = atributos->begin();
			this->archivo.write((char*)&tamanioInstanciaNuevo,sizeof(tamanioInstanciaNuevo));
			for (list<metaDataAtributo>::iterator it = listaTipoAtributos->begin(); it != listaTipoAtributos->end(); it++,it2++) {
				if (it->tipo == TEXTO) {
					this->archivo.write(it2->texto,strlen(it2->texto));
					this->archivo.write(&separadorString,1);
				} else {
					this->archivo.write((char*)&(it2->entero),it->cantidadBytes);
				}
			}
			//Muevo lo q esta para atras
			int diferencia = tamanioInstanciaViejo - tamanioInstanciaNuevo;
			int espacioACopiar = 8 + (bloqueActual + 1) * tamanioBloque - (pos + tamanioInstanciaViejo);
			char* buffer = new char[espacioACopiar];
			archivo.seekg(0,ios::end);
			if (pos + tamanioInstanciaViejo + espacioACopiar >= archivo.tellg()){
				espacioACopiar = archivo.tellg() - pos - tamanioInstanciaViejo;
			}
			archivo.seekg(pos + tamanioInstanciaViejo,ios::beg);
			archivo.read(buffer,espacioACopiar);

			archivo.seekp(pos + tamanioInstanciaNuevo,ios::beg);
			archivo.write(buffer,espacioACopiar);
			this->vectorBloques[bloqueActual]->setEspacioLibre(this->vectorBloques[bloqueActual]->getEspacioLibre() + diferencia);
		}



	}
	return -1;
}


