/*
	MMB Library
*/

#ifndef MMB_H
#define MMB_H

#include "Arduino.h"
#include "Client.h"
#include <String.h>
#include <Flash.h>
#include <HttpClient.h>

#include "MMBParameter.h";


//debug
#define DEBUG 1

#define MMB_API_HOSTNAME "api.mymicrobridge.com"

#define MAX_PARAMETER 10

//MMB class
class MMB {
	
	public:
		MMB(Client& client); //costructor
		~MMB(); //destroyer

		void setAccountName(const char *account); //set account name
		void setAPIName(const char *api); //set API name

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

		char *buildResourceURL(); //build API URL

		Client *_client; //net client (client passato)
		HttpClient _http; //http client (SimpleHttpClient library)

		const char *_account; //user account name
		const char *_api; //user API name

		int _pos;

		MMBParameter *_params[MAX_PARAMETER]; //array per i parametri


};

#endif