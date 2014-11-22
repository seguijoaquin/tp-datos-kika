
#include <stdio.h>
#include <iostream>

#include "Capa Usuario/Interfaz.h"

int main(){

	Interfaz* iu = new Interfaz();
	cout << "75.06 - ORGANIZACION DE DATOS"<<endl<<
			"TRABAJO PRACTICO"<<endl<<
			"GESTOCK Y VENTAS"<<endl<<endl<<endl;
	while(iu->listar_opciones_menu_principal()){
		cout << endl;
	}
	cout << "Adiós." <<endl;
	delete iu;
	return 0;
}
