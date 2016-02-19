/*
	MMBParameter Library
*/

#ifndef MMBPARAMETER_H
#define MMBPARAMETER_H

#include "Arduino.h"

//tipi di parametri (gli altri sono mantenuti all'interno del portale e quindi non hanno accesso verso l'esterno)
#define MMB_PARAMETER_QUERY_STRING 1
#define MMB_PARAMETER_X_WWW_FORM_URLENCODED 2
#define MMB_PARAMETER_URI_TEMPLATE 3


//debug
#define DEBUG 1


//MMB class
class MMBParameter {

	public:
		MMBParameter(int type, char *offset, char *value); //constructor
		MMBParameter(int type, int position, char *value); //constructor
		~MMBParameter(); //destroyer

		//get
		int getType();
		char *getOffset();
		int getPosition();
		char *getValue();



	private:

		MMBParameter(int type, char *offset, int position, char *value);

		int _type; //tipo di parametro
		char *_offset; //offset

		int _position; //position se usato (URI_TEMPLATE)
		char *_value; //value se usato (QUERY_STRING o X_WWW_FORM_URLENCODED)



};

#endif
