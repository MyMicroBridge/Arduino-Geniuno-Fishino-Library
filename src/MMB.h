/*
	MMB Library
*/

#ifndef MMB_H
#define MMB_H

#include "Arduino.h"
#include "Client.h"
#include <String.h>
#include <Flash.h>


//debug
#define DEBUG 1

#define MMB_API_BASE_URL "api.mymicrobridge.com"

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


		//---DEBUG---
		void printDataDebug();

		void debugPrint(const char *msg);

	private:

		char *buildResourceURL(); //build API URL


		Client *_client; //net client

		const char *_account; //user account name
		const char *_api; //user API name


};

#endif