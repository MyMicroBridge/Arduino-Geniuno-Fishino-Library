/*
	MMB Library
*/

#ifndef MMB_H
#define MMB_H

#include "Arduino.h"
#include "Client.h"
#include <HttpClient.h>

#include "MMBParameter.h";


//debug
#define DEBUG 1

#define MMB_API_HOSTNAME "api.mymicrobridge.com"

#define MAX_PARAMETER 10 //numero massimo di parametri
#define RESOURCE_BUFFER_DIMENSION 255 //dimensione dell'array per tenere l'URL della API
#define RESOURCE_PARAMETER_BUFFER_DIMENSION 255

//MMB class
class MMB {
	
	public:
		MMB(Client& client); //costructor
		~MMB(); //destroyer

		void setAccountName(char *account); //set account name
		void setAPIName(char *api); //set API name

		int run(); //execute API

		//lettura risposta
		int available();
		int read();
		void close();

		//aggiunta parametri
		int addParameter(MMBParameter& parameter);


		//---DEBUG---
		void printDataDebug();

		void debugPrint(String msg);

	private:

		void buildResourceURL(); //build API URL
		void buildQueryStringParameter(char *offset, char *value); //costruisce il parametro queryString

		Client *_client; //net client (client passato)
		HttpClient _http; //http client (SimpleHttpClient library)

		char *_account; //user account name
		char *_api; //user API name

		int _pos;

		MMBParameter *_params[MAX_PARAMETER]; //array per i parametri

		char _resource[RESOURCE_ARRAY_DIMENSION]; //stringa per la risorsa



};

#endif