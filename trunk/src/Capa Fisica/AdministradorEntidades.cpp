#include "AdministradorEntidades.h"


AdministradorEntidades::AdministradorEntidades(){
	this->archivo.open("entidades.txt",std::ios_base::in | std::ios_base::out |std::ios_base::app);
	this->listaEntidades = new list<Entidad>;
}

AdministradorEntidades::~AdministradorEntidades(){
	this->archivo.close();
	this->listaEntidades->clear();
	delete this->listaEntidades;
}

void AdministradorEntidades::finalizarEntidad() {
	this->archivo << '\n';
}

void AdministradorEntidades::leerArchivoEntidades(){
	std::fstream arch;
	arch.open("entidades.txt");
	std::string str;
	std::getline(arch,str);
	while (!arch.eof() && !str.empty()) {
		char* cstr = new char [str.length()+1];
		std::strcpy (cstr, str.c_str());
		std::string p = std::strtok (cstr,"@"); //Separo ID
		int id = std::atoi(p.c_str());

		p = std::strtok(NULL,"@"); //Separo Nombre
		std::string nombreEntidad = p;

		p = std::strtok(NULL,"@"); //Separo tipo
		std::string tipo_l = p;
		TipoArchivo tipoArchivo;
		if (tipo_l == "FIJO") tipoArchivo = FIJO;
		if (tipo_l == "DEBLOQUES") tipoArchivo = DEBLOQUES;
		if (tipo_l == "VARIABLE") tipoArchivo = VARIABLE;

		p = std::strtok(NULL,"@"); //Separo cantidad atributos
		int cantAtributos = std::atoi(p.c_str());

		list<metaDataAtributo>* listaAtribs = new list<metaDataAtributo>;
		for (int j=1;j<=cantAtributos;++j) {
			p = std::strtok(NULL,"@"); //Separo nombre
			std::string nombreAtributo = p;
			p = std::strtok(NULL,"@"); //Separo ID entidad
			int id_entidad = std::atoi(p.c_str());
			p = std::strtok(NULL,"@"); //Separo tipo
			std::string tipoAtrib = p;
			TipoAtributo tipoAtributo;
			if (tipoAtrib == "ENTERO") tipoAtributo = ENTERO;
			if (tipoAtrib == "TEXTO") tipoAtributo = TEXTO;
			if (tipoAtrib == "ENTID") tipoAtributo = ENTID;
			p = std::strtok(NULL,"@"); //Separo cantidad Bytes
			int cantidadBytes = std::atoi(p.c_str());
			metaDataAtributo* nuevoAtributo = new metaDataAtributo();
			nuevoAtributo->nombre = nombreAtributo;
			nuevoAtributo->tipo = tipoAtributo;
			nuevoAtributo->cantidadBytes = cantidadBytes;
			nuevoAtributo->idEntidad = id_entidad;
			listaAtribs->push_back(*nuevoAtributo);
		}
		Entidad* nuevaEntidad = new Entidad(listaAtribs,nombreEntidad,id,tipoArchivo);
		nuevaEntidad->leerInstancias();
		this->listaEntidades->push_back(*nuevaEntidad);
		std::getline(arch,str);
		delete[] cstr;
	}
	arch.close();
}

void AdministradorEntidades::agregarDato(string buffer) {
	//this->archivo.write(buffer.c_str(),buffer.size());
	this->archivo << buffer;
	this->archivo << '@';
}

void AdministradorEntidades::agregarDato(int buffer) {
	this->archivo << buffer;
	this->archivo << '@';
}

int AdministradorEntidades::getUltimoID() {
	if(this->listaEntidades->empty()) return 0;
	return this->listaEntidades->back().getID();
}

void AdministradorEntidades::agregarAtributo(metaDataAtributo atributo) {
	this->agregarDato(atributo.nombre);
	this->agregarDato(atributo.idEntidad);
	switch (atributo.tipo) {
			case ENTERO:	this->agregarDato("ENTERO");
							break;
			case TEXTO: 	this->agregarDato("TEXTO");
							break;
			case ENTID: 	this->agregarDato("ENTID");
							break;
			default:		this->agregarDato("DEFAULT");
							break;
		}
	this->agregarDato(atributo.cantidadBytes);
}

void AdministradorEntidades::crearEntidad(Entidad* entidad){
	this->archivo.seekg(0,this->archivo.end); //me posiciono al final del archivo
	this->listaEntidades->push_back(*entidad); //agrego entidad a la lista
	this->agregarDato(entidad->getID());
	this->agregarDato(entidad->getNombre());
	switch (entidad->getTipoArchivo()) {
		case FIJO:		this->agregarDato("FIJO");
						break;
		case VARIABLE: 	this->agregarDato("VARIABLE");
						break;
		case DEBLOQUES: this->agregarDato("DEBLOQUES");
						break;
		default:		this->agregarDato("DEFAULT");
						break;
	}
	this->agregarDato(entidad->getListaAtributos()->size());
	list<metaDataAtributo>::iterator it = entidad->getListaAtributos()->begin();
	while (it != entidad->getListaAtributos()->end()) {
		this->agregarAtributo(*it);
		++it;
	}
	this->finalizarEntidad();
}

void AdministradorEntidades::listarEntidades() {
	list<Entidad>::iterator it = this->listaEntidades->begin();
	int cont = 1;
	while( it != this->listaEntidades->end() )
	{
		cout << cont << " " << it->getNombre() << endl;
		++cont;
		++it;
	}
	cout << "------------------" << endl;
}

void AdministradorEntidades::listarInstancias(int id){
	list<Entidad>::iterator it = this->listaEntidades->begin();
	int i = 1;
	while( i < id ){
		++i;
		++it;
	}
	it->listarInstancias();
}

int AdministradorEntidades::getID(int x) {
	list<Entidad>::iterator it = listaEntidades->begin();
	if (x > this->listaEntidades->size() | x < 0) {
		return 0;
	}
	for(int i = 1 ; i < x ;++i) {
		++it;
	}
	return it->getID();
}

void AdministradorEntidades::crearInstancia(int id){

	Entidad* ent = this->getEntidad(id);
	Entidad* auxEnt;
	char opget[5];
	list<Atributo>* listaDatos = new list<Atributo>;
	cout<<"Ingresar atributos:"<<endl;
	list<metaDataAtributo>::iterator iterAtts = ent->getListaAtributos()->begin();

	Atributo aux;

	// Agrega el ID.
	aux.entero = ent->getUltimoIDInstancia() + 1;
	listaDatos->push_back(aux);
	iterAtts++;

	while(iterAtts != ent->getListaAtributos()->end()){

		if (iterAtts->tipo == ENTERO){
			cout<<iterAtts->nombre<<"(entero): ";
			cin>>aux.entero;

		}else if(iterAtts->tipo == ENTID){

			// No hay instancia de la entidad pedida.

			cout<<iterAtts->nombre<<"(entidad)"<<endl;

			auxEnt = this->getEntidad(iterAtts->idEntidad); // Entidad de la que pide.
			auxEnt->listarInstancias();

			cout << "Ingrese el ID de la instancia que desea utilizar: ";
			Instancia* instancia;
			do {
				cin >> opget;
				cout << endl;
				cin.get();
				aux.entero = atoi(opget);
				instancia = auxEnt->getInstancia(aux.entero);
				if (instancia == NULL) {
					cout<<"Opción ingresada es incorrecta."<<endl;
				}
			} while (instancia == NULL);

		}else {
			cout<<iterAtts->nombre<<"(max "<<iterAtts->cantidadBytes<<"): ";
			aux.texto = new char[maxCantidadCaracteres];
			do {
				cin>>aux.texto;
				if (strlen(aux.texto) > iterAtts->cantidadBytes) cout<<"La cantidad de caracteres excede el maximo permitido. Ingrese nuevamente el valor: ";
			} while (strlen(aux.texto) > iterAtts->cantidadBytes);
		}
		listaDatos->push_back(aux);
		iterAtts++;
	}
	ent->crearInstancia(listaDatos);
}

Entidad* AdministradorEntidades::getEntidad(int id){
	list<Entidad>::iterator it = listaEntidades->begin();
	for(int i = 1 ; i < id ;++i) {
		++it;
	}
	return &(*it);
}

void AdministradorEntidades::modificarInstancia(unsigned int id, unsigned int id_instancia){

	Entidad* ent = this->getEntidad(id);
	Instancia* inst = ent->getInstancia(id_instancia);
	if(!inst){
		cout<<"Opción ingresada es incorrecta."<<endl;
		return;
	}

	list<metaDataAtributo>* metaAtts = ent->getListaAtributos(); // Metadata de atibutos.
	list<Atributo>* atts = inst->getListaAtributos();	// Vieja lista de atributos.
	list<Atributo>* newAtts = new list<Atributo>;		// Nueva lista de atributos.
	Atributo* atributo;
	Entidad* auxEnt;

	list<metaDataAtributo>::iterator metaIter = metaAtts->begin();
	list<Atributo>::iterator iter = atts->begin();

	metaIter++; //Salteo atributo de ID.
	iter++;		//Salteo atributo de ID.

	// Guardo el atributo ID.
	atributo = new Atributo();
	atributo->entero = inst->getID();
	newAtts->push_back(*atributo);


	// Variables auxiliares para leer entrada de usuario.
	char opget[5];
	int auxInt;
	char* auxChar;

	// Pregunta nuevos valores de atributos.
	while(metaIter != metaAtts->end()){
		if(metaIter->tipo == ENTERO){
			cout<<endl;
			cout<<"Valor anterior del atributo "<<metaIter->nombre<<", de tipo int: "<<iter->entero<<endl;
			cout<<"Ingrese el nuevo valor: ";
			cin >> opget;
			cout <<endl;
			cin.get();
			auxInt = atoi(opget);

			//  Crear nuevo atributo.
			atributo = new Atributo();
			atributo->entero = auxInt;

		}else if(metaIter->tipo == TEXTO){
			cout<<endl;
			auxChar = new char[metaIter->cantidadBytes+1];
			//std::string auxChar;
			cout<<"Valor anterior del atributo "<<metaIter->nombre<<", de tipo string (max " << metaIter->cantidadBytes<<" caracateres):"<<iter->texto<<endl;
			cout<<"Ingrese el nuevo valor: ";
			do {
				cin >> auxChar;
				if (strlen(auxChar) > metaIter->cantidadBytes) cout<<"La cantidad de caracteres excede el maximo permitido. Ingrese nuevamente el valor: ";
			} while (strlen(auxChar) > metaIter->cantidadBytes);

			// Crear nuevo atributo.
			atributo = new Atributo();
			atributo->texto = auxChar;

		}else{ // Entidad X

			auxEnt = this->getEntidad(metaIter->idEntidad); // Entidad de la que pide.
			cout << "Modificacion del atributo entidad " << auxEnt->getNombre() << ":" << endl;
			auxEnt->listarInstancias();
			cout << "Ingrese el ID de la nueva instancia que desea utilizar: ";
			cin >> opget;
			cout << endl;
			cin.get();
			auxInt = atoi(opget);

			//  Crear nuevo atributo.
			atributo = new Atributo();
			atributo->entero = auxInt;
		}
		newAtts->push_back(*atributo);
		metaIter++;
		iter++;
	}
	ent->modificarInstancia(id_instancia, metaAtts, newAtts);
}

void AdministradorEntidades::eliminarInstancia(unsigned int id, unsigned int id_instancia){
	Entidad* ent = this->getEntidad(id);
	ent->eliminarInstancia(id_instancia);
}

void AdministradorEntidades::eliminarInstancias(int id){
	this->getEntidad(id)->eliminarInstancias();
}

bool AdministradorEntidades::entidadExistente(string nombre){
	list<Entidad>::iterator it = this->listaEntidades->begin();
	while( it != this->listaEntidades->end() ){
		if(it->getNombre() == nombre){
			return true;
		}
		++it;
	}
	return false;
}


