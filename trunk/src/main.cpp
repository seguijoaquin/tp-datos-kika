
#include <stdio.h>
#include <iostream>

#include "Interfaz.h"

int main(){

	Interfaz* iu = new Interfaz();
	unsigned int opc = 0;
	while(opc != 7){
		cout << endl;
		iu->listar_opciones();
		opc = iu->pedir_opcion();
		if(iu->ejecutar_opcion(opc)){
			// Se ejecuto la opción.
		}else if(opc == 7){
			cout<<"Adios."<<endl;
		}else{
			cout<<"La opción seleccionada es incorrecta."<<endl;
		}
	}
	delete iu;
	return 0;
}
