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

	char opget[1];
	cout << " Numero de opcion:";
	cin >> opget;
	int opgeti = atoi(opget);
	cout << " \n";
	cin.get();
	cout << "Usted seleccionó la opción: " << opgeti << "\n";
	return opgeti;
}

bool Interfaz::ejecutar_opcion(unsigned int opc){

	switch (opc){
		case 1:	// Crear nueva entidad.
			cout << "Opcion 1.\n";
			break;
		case 2: // Crear nueva instancia.
			cout << "Opcion 2.\n";
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
