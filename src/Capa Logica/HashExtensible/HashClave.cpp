
#include "HashClave.h"

HashClave::HashClave(string valor,bool desSerealizar){
	if(desSerealizar){
		key="";
		desSerializar(valor);
	}else{
		key = valor;
	}
}


ostream& operator<< (ostream& os, const HashClave& ptrObj){
	os << ptrObj.key;
	return os;
}


string HashClave::serializar()const{
	//return key.serializar();
	string strRetorno;
	ostringstream retorno;
	retorno << key;
	strRetorno = retorno.str();
	return strRetorno;
}

void HashClave::desSerializar(const string elemSerializado){
	key = elemSerializado;
}

bool HashClave::operator==  (const HashClave& other) const{
	return key == other.key;
}

bool HashClave::operator!=  (const HashClave& other) const{
	return key != other.key;
}

int HashClave::hashear(const int& mod)const{
	//usamos dispersion modular
	int asciTotal=0;
    for(unsigned int i=0;i< key.size();i++){
    	asciTotal += (int)key[i];
    }

    return (asciTotal%mod);
}

HashClave::~HashClave(){
	if (key != "") {
		//delete key;
	}
}
