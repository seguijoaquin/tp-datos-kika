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
		//nuevaEntidad->leerInstancias();
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

/*void AdministradorEntidades::crearEntidad(Entidad* entidad){
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
}*/

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
	if (this->listaEntidades->empty()) {
		cout << "No hay instancias de esta entidad" << endl;
	} else {
		list<Entidad>::iterator it = this->listaEntidades->begin();
		int i = 1;
		while( i < id ){
			++i;
			++it;
		}
		it->listarInstancias();
	}

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

Instancia* AdministradorEntidades::crearInstancia(int id){

	Entidad* ent = this->getEntidad(id);
	if (!this->validarCreacionInstancia(ent)) {
		return NULL;
	}
	Entidad* auxEnt;
	char opget[5];
	list<Atributo>* listaDatos = new list<Atributo>;
	cout<<"Ingresar atributos:"<<endl;
	list<metaDataAtributo>::iterator iterAtts = ent->getListaAtributos()->begin();

	Atributo aux;
	// Agrega el ID.
	aux.entero = ent->getUltimoIDInstancia() + 1;
	int id_instancia = aux.entero;
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

			cout << "Ingrese el ID de la instancia que desea utilizar o 0 si no quiere utilizar ninguna: ";
			bool error,valido;
			do {
				cin >> opget;
				cout << endl;
				cin.get();
				aux.entero = atoi(opget);

				auxEnt->getInstancia(aux.entero,error);
				valido = this->validarIdCreacionInstancia(ent,aux.entero,iterAtts->nombre);
				if (error && !valido) {
					cout<<"Opción ingresada es incorrecta."<<endl;
				}
			} while (error && !valido);

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
	bool error;
	return ent->getInstancia(id_instancia,error);
}

bool AdministradorEntidades::validarIdCreacionInstancia(Entidad* ent,int id_instancia,string nombreAtributo){
	//Valido debe existir fabricante para crear familia
	if (ent->getNombre() == "Familia") {
		if ((nombreAtributo == "Fabricante") && (id_instancia == 0)) {
			cout<<"No puede ingresar 0 como ID en este caso"<<endl;
			return false;
		}
		return true;
	}
	//Debe existir familia, parte y material  para crear producto
	if (ent->getNombre() == "Producto") {
		if ((nombreAtributo == "Familia" || nombreAtributo == "Partes" || nombreAtributo == "Material") && id_instancia == 0) {
			cout<<"No puede ingresar 0 como ID en este caso"<<endl;
			return false;
		}
		return true;
	}
	//Debe existir contorno-copa-bretel para crear partes
	if (ent->getNombre() == "Partes") {
		if ((nombreAtributo == "Contorno" || nombreAtributo == "Copa" || nombreAtributo == "Bretel") && id_instancia == 0) {
			cout<<"No puede ingresar 0 como ID en este caso"<<endl;
			return false;
		}
		return true;
	}
	return true;
}

Entidad* AdministradorEntidades::getEntidad(int id){
	list<Entidad>::iterator it = listaEntidades->begin();
	for(int i = 1 ; i < id ;++i) {
		++it;
	}
	return &(*it);
}

void AdministradorEntidades::modificarInstancia(unsigned int id, unsigned int id_instancia,Instancia** instanciaVieja, Instancia** instanciaNueva){

	Entidad* ent = this->getEntidad(id);
	bool error;
	Instancia* inst = ent->getInstancia(id_instancia,error);
	(*instanciaVieja) = inst;
	if(error){
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
	ent->modificarInstancia(id_instancia, newAtts);
	(*instanciaNueva) = ent->getInstancia(id_instancia,error);
}

Instancia* AdministradorEntidades::eliminarInstancia(unsigned int id, unsigned int id_instancia){
	Entidad* ent = this->getEntidad(id);
	vector<Eliminados>* instanciasAfectadas = this->informarEliminacion(ent,id_instancia);
	Instancia* retorno = NULL;
	bool error;
	if (instanciasAfectadas == NULL) {
		retorno = ent->getInstancia(id_instancia,error);
		ent->eliminarInstancia(id_instancia);
	} else {
		if (instanciasAfectadas->size() == 0) {
			retorno = ent->getInstancia(id_instancia,error);
			ent->eliminarInstancia(id_instancia);
		} else {
			cout<<"Eliminar esta instancia eliminara: ";
			for (int i = 0; i < instanciasAfectadas->size();i++) {
				Eliminados eliminados = instanciasAfectadas->at(i);
				Entidad* entidad = this->getEntidad(eliminados.idEntidad);
				cout<<eliminados.idInstancias->size()<<" instancias de la entidad "<<entidad->getNombre()<<", ";
			}
			char respuesta;
			do
			{
				cout << "Desea continuar? [y/n]" << endl;
				cin >> respuesta;
			}
			while( !cin.fail() && respuesta!='y' && respuesta!='n' );
			if (respuesta == 'y') {
				for (int i = 0; i < instanciasAfectadas->size();i++) {
					Eliminados eliminados = instanciasAfectadas->at(i);
					Entidad* entidad = this->getEntidad(eliminados.idEntidad);
					for (int j = 0; j < eliminados.idInstancias->size(); j++) {
						entidad->eliminarInstancia(eliminados.idInstancias->at(j));
					}
				}
				retorno = ent->getInstancia(id_instancia,error);
				ent->eliminarInstancia(id_instancia);
			}
		}
	}
	return retorno;
}

vector<Eliminados>* AdministradorEntidades::informarEliminacion(Entidad* ent,unsigned int id_instancia) {

	if (ent->getNombre() == "Fabricante" || ent->getNombre() == "Bretel" || ent->getNombre() == "Contorno" || ent->getNombre() == "Copa" || ent->getNombre() == "Tintura" ) {
		return this->eliminacionIndirecta(ent,id_instancia);
	}
	if (ent->getNombre() == "Familia" || ent->getNombre() == "Partes" || ent->getNombre() == "Material") {
		return this->eliminacionDirecta(ent,id_instancia);
	}
	if (ent->getNombre() == "Color" || ent->getNombre() == "Estampa" || ent->getNombre() == "Aro" || ent->getNombre() == "Formadores" || ent->getNombre() == "Tintura" ) {
		return this->eliminacionInIndirecta(ent,id_instancia);
	}
	return NULL;
}

vector<Eliminados>* AdministradorEntidades::eliminacionDirecta(Entidad* ent,int id_instancia){
	vector<Eliminados>* instanciasAfectadas = new vector<Eliminados>;
	Eliminados e;
	Entidad* productos = this->getEntidad(14);

	unsigned int nroAtributo;
	if (ent->getNombre() == "Familia") {
		nroAtributo = 3;
	} else {
		if (ent->getNombre() == "Partes") {
			nroAtributo = 4;
		} else {
			if (ent->getNombre() == "Material") {
				nroAtributo = 6;
			}
		}
	}

	vector<int>* idInstancias = new vector<int>;
	for (int i = 1; i <= productos->getUltimoIDInstancia(); i++) {
		bool error;
		Instancia * producto = productos->getInstancia(i,error);
		if (!error) {
			Atributo* atributo = producto->getAtributo(nroAtributo);
			if (atributo->entero == id_instancia) {
				idInstancias->push_back(i);
			}
		}
	}
	e.idEntidad = 14;
	e.idInstancias = idInstancias;
	instanciasAfectadas->push_back(e);

	return instanciasAfectadas;
}

vector<Eliminados>* AdministradorEntidades::eliminacionIndirecta(Entidad* ent,int id_instancia){
	vector<Eliminados>* instanciasAfectadas = new vector<Eliminados>;
	Eliminados e;
	Entidad* productos = this->getEntidad(14);

	int nroEntidad;
	int nroAtributoProducto;
	int nroAtributoEntidad;
	if (ent->getNombre() == "Fabricante") {
		nroEntidad = 10;	//Fabricante va a familia
		nroAtributoProducto = 3;	//Familia es 3er atributo en producto
		nroAtributoEntidad = 3;		//Fabricante es 3er atributo en familia
	} else if (ent->getNombre() == "Bretel") {
		nroEntidad = 13;	//Bretel va a Partes
		nroAtributoProducto = 4;
		nroAtributoEntidad = 4;
	} else if (ent->getNombre() == "Contorno") {
		nroEntidad = 13;	//Contorno va a Partes
		nroAtributoProducto = 4;
		nroAtributoEntidad = 2;
	} else if (ent->getNombre() == "Copa") {
		nroEntidad = 13;	//Copa va a Partes
		nroAtributoProducto = 4;
		nroAtributoEntidad = 3;
	} else if (ent->getNombre() == "Tintura") {
		nroEntidad = 13;	//Tintura va a Partes
		nroAtributoProducto = 4;
		nroAtributoEntidad = 5;
	}
	vector<int>* instanciasAEliminar = new vector<int>;
	vector<int>* productosAEliminar = new vector<int>;
	Entidad* entidad = this->getEntidad(nroEntidad);
	for (int i = 1; i <= entidad->getUltimoIDInstancia(); i++) { //Ej: recorro familias buscando fabricantes q matchean
		bool error;
		Instancia* instancia = entidad->getInstancia(i,error);
		if (!error) {
			Atributo* atributo = instancia->getAtributo(nroAtributoEntidad);	//Ej: ID de instancia de un fabricante
			if (atributo->entero == id_instancia) {
				instanciasAEliminar->push_back(i);
			}
		}
	}
	for (int i = 1; i <= productos->getUltimoIDInstancia(); i++) { //Ej: recorro productos buscando familias q matchean
		bool error;
		Instancia* producto = productos->getInstancia(i,error);
		if (!error) {
			Atributo* atributo = producto->getAtributo(nroAtributoProducto);	//Ej: Tengo ID de una instancia de familia
			bool encontrado = false;
			for (int j = 0; j < instanciasAEliminar->size() && !encontrado; j++) {
				if (atributo->entero == instanciasAEliminar->at(j)) {
					productosAEliminar->push_back(i);
					encontrado = true;
				}
			}
		}
	}

	if (instanciasAEliminar->size() != 0) {
		e.idEntidad = nroEntidad; e.idInstancias = instanciasAEliminar; instanciasAfectadas->push_back(e);
		if (productosAEliminar->size() != 0) {
			e.idEntidad = 14; e.idInstancias = productosAEliminar; instanciasAfectadas->push_back(e);
		}
	}

	return instanciasAfectadas;
}

vector<Eliminados>* AdministradorEntidades::eliminacionInIndirecta(Entidad* ent,int id_instancia){
	vector<Eliminados>* instanciasAfectadas = new vector<Eliminados>;
	Eliminados e;
	Entidad* productos = this->getEntidad(14);

	int nroEntidad;
	int nroAtributoPartes;
	int nroAtributoEntidad;
	if (ent->getNombre() == "Color") {
		nroEntidad = 12;	//Tintura
		nroAtributoPartes = 5;	//Tintura
		nroAtributoEntidad = 2;		//Color es 2do atributo en tintura
	} else if (ent->getNombre() == "Estampa") {
		nroEntidad = 12;	//Tintura
		nroAtributoPartes = 5;	//Tintura
		nroAtributoEntidad = 3;
	} else if (ent->getNombre() == "Aro") {
		nroEntidad = 11;	//Copa
		nroAtributoPartes = 3;	//Copa
		nroAtributoEntidad = 4;
	} else if (ent->getNombre() == "Formadores") {
		nroEntidad = 11;	//Copa
		nroAtributoPartes = 3; //Copa
		nroAtributoEntidad = 3;
	}
	vector<int>* instanciasAEliminar = new vector<int>;
	vector<int>* partesAEliminar = new vector<int>;
	vector<int>* productosAEliminar = new vector<int>;
	Entidad* partes = this->getEntidad(13);
	Entidad* entidad = this->getEntidad(nroEntidad);
	for (int i = 1; i <= entidad->getUltimoIDInstancia(); i++) { //Ej: recorro tinturas buscando colores q matchean
		bool error;
		Instancia* instancia = entidad->getInstancia(i,error);
		if (!error) {
			Atributo* atributo = instancia->getAtributo(nroAtributoEntidad);
			if (atributo->entero == id_instancia) {
				instanciasAEliminar->push_back(i);
			}
		}
	}
	for (int i = 1; i <= partes->getUltimoIDInstancia(); i++) { //Ej: recorro partes buscando tinturas q matchean
		bool error;
		Instancia* parte = partes->getInstancia(i,error);
		if (!error) {
			Atributo* atributo = parte->getAtributo(nroAtributoPartes);	//Ej: Tengo ID de una instancia de tintura
			bool encontrado = false;
			for (int j = 0; j < instanciasAEliminar->size() && !encontrado; j++) {
				if (atributo->entero == instanciasAEliminar->at(j)) {
					partesAEliminar->push_back(i);
					encontrado = true;
				}
			}
		}
	}
	for (int i = 1; i <= productos->getUltimoIDInstancia(); i++) {
		bool error;
		Instancia* producto = productos->getInstancia(i,error);
		if (!error) {
			Atributo* atributo = producto->getAtributo(4);	//Ej: Tengo ID de una instancia de partes
			bool encontrado = false;
			for (int j = 0; j < partesAEliminar->size() && !encontrado; j++) {
				if (atributo->entero == partesAEliminar->at(j)) {
					productosAEliminar->push_back(i);
					encontrado = true;
				}
			}
		}
	}
	if (instanciasAEliminar->size() != 0) {
		e.idEntidad = nroEntidad; e.idInstancias = instanciasAEliminar; instanciasAfectadas->push_back(e);
		if (partesAEliminar->size() != 0) {
			e.idEntidad = 13; e.idInstancias = partesAEliminar; instanciasAfectadas->push_back(e);
			if (productosAEliminar->size() != 0) {
				e.idEntidad = 14; e.idInstancias = productosAEliminar; instanciasAfectadas->push_back(e);
			}
		}
	}
	return instanciasAfectadas;
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

bool AdministradorEntidades::validarCreacionInstancia(Entidad* ent) {
	//Valido debe existir fabricante para crear familia
	if (ent->getNombre() == "Familia") {
		Entidad* entidad = this->getEntidad(1); //Entidad 1 = Fabricante
		if (entidad->getCantidadInstancias() == 0){
			cout<<"Debe existir un fabricante para crear una familia"<<endl;
			return false;
		}
		return true;
	}
	//Debe existir familia, parte y material  para crear producto
	if (ent->getNombre() == "Producto") {
		Entidad* entidad = this->getEntidad(10); //Entidad 10 = Familia
		if (entidad->getCantidadInstancias() == 0){
			cout<<"Debe existir una familia para crear un producto"<<endl;
			return false;
		}
		entidad = this->getEntidad(13); //13 = partes
		if (entidad->getCantidadInstancias() == 0){
			cout<<"Deben existir partes para crear un producto"<<endl;
			return false;
		}
		entidad = this->getEntidad(5); //5 = material
		if (entidad->getCantidadInstancias() == 0){
			cout<<"Debe existir un material para crear un producto"<<endl;
			return false;
		}
		return true;
	}
	//Debe existir contorno-copa-bretel para crear partes
	if (ent->getNombre() == "Partes") {
		Entidad* entidad = this->getEntidad(11); //Entidad 11 = Copa
		if (entidad->getCantidadInstancias() == 0){
			cout<<"Debe existir una copa para crear partes"<<endl;
			return false;
		}
		entidad = this->getEntidad(2); //2 = Contorno
		if (entidad->getCantidadInstancias() == 0){
			cout<<"Debe existir un contorno para crear partes"<<endl;
			return false;
		}
		entidad = this->getEntidad(6); //6 = Bretel
		if (entidad->getCantidadInstancias() == 0){
			cout<<"Debe existir un bretel para crear partes"<<endl;
			return false;
		}
		return true;
	}
	return true;
}

