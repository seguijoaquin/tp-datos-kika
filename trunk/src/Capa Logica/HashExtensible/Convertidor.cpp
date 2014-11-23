#include "Convertidor.h"

int Convertidor::stringToInt(const string& valor){
	int retorno;
	istringstream stream(valor);
	return stream>>retorno? retorno:-1;
}

string Convertidor::intToString(const int& valor){
	string s;
	stringstream retorno;
	retorno << valor;
	s = retorno.str();
	return s;
}

