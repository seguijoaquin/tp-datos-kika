
#include <stdio.h>
#include <iostream>

#include "Capa Fisica/AdministradorEntidades.h"

int main() {

	AdministradorEntidades* adminEntidades = new AdministradorEntidades();
	adminEntidades->leerArchivoEntidades();
	adminEntidades->menuUsuario();

	return 0;
}
