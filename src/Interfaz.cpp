#include "Interfaz.h"

Interfaz::Interfaz(){

	this -> opciones = new list<string>;
	this -> opciones -> push_back("Crear nueva Entidad.");
	this -> opciones -> push_back("Crear nueva Instancia.");
	this -> opciones -> push_back("Modificar Instancia.");
	this -> opciones -> push_back("Eliminar instancia.");
	this -> opciones -> push_back("Eliminar todas las instancias.");
	this -> opciones -> push_back("Listar instancias.");
}

void Interfaz::listar_opciones(){

	cout << "Ingrese el número de la opcion seleccionada:\n";
	int cont = 1;
	list<string>::iterator it = this->opciones->begin();
	while( it != this->opciones->end() )
	{
		cout << "	" << cont << ") " << *it++ << "\n";
		cont++;
	}
}

unsigned int Interfaz::pedir_opcion(){

	char opget[5];
	cout << " Numero de opcion: ";
	cin >> opget;
	cout << " \n";
	cin.get();
	return atoi(opget);
}

void Interfaz::crear_entidad(){
	
	cout << "Ingrese el nombre de la entidad: ";
	char nombre_entidad[50];
	cin >> nombre_entidad;
	
	// Verificar que no exista.
	
	int indice = 1;
	int opget = 0;
	while(true){
	/*  Pide atributos hasta que la opción de tipo de atributo sea *
	 *     diferente de las existentes, deja de pedir atributos.   */
	 
		cout << "\n Atributo N°" << indice << ": \n  Tipo de atributo: \n";
		cout << "    1. Entero.\n    2. Cadena de caracteres.\n    3. Entidad X.\n";
		opget = this -> pedir_opcion();
		
		if( opget > 3 || opget < 1 ){break;}
		
		cout << "Ingrese el nombre del atributo: ";
		char nombre_att[50];
		cin >> nombre_att;
		cout << "\n";
		
		switch(opget){
		/* Tipo de atributo seleccionado */
		
			case 1: // Entero

				break;

			case 2: // Cadena de caracteres

				break;

			case 3: // Entidad X
			
				break;
		}
		
		indice ++;
	}
	
}

void Interfaz::crear_instancia(){
	
}

bool Interfaz::ejecutar_opcion(unsigned int opc){

	switch (opc){
		case 1:	// Crear nueva entidad.
			this->crear_entidad();
			break;
		case 2: // Crear nueva instancia.
			this->crear_instancia();
			break;
		case 3: // Modificar instancia.
			cout << "Opcion 3.\n";
			break;
		case 4: // Eliminar instancia.
			cout << "Opcion 4.\n";
			break;
		case 5: // Eliminar todas las instancias.
			cout << "Opcion 5.\n";
			break;
		case 6: // Listar instancias.
			cout << "Opcion 6.\n";
			break;
		default:
			return false;
	}
	return true;
}


/*--------------------------------------------------------------------*/

int main(){

	Interfaz* iu = new Interfaz();
	cout << "\n";
	iu -> listar_opciones();
	unsigned int opc = iu -> pedir_opcion();
	if(iu -> ejecutar_opcion(opc)){
		// Se ejecuto la opción.
	}else{
		cout << "La opción seleccionada es incorrecta.\n";
	}
	return 0;
}
