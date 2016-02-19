/*
	MMB Library
*/

#ifndef MMB_H
#define MMB_H

#include "Arduino.h"
#include "Client.h"
#include <HttpClient.h>


//debug
#define DEBUG 1

#define MMB_API_HOSTNAME "api.mymicrobridge.com"

#define API_URL_MAX_LENGTH 200 //buffer API URL
#define QUERY_STRING_MAX_LENGTH 50 //buffer parametri query string
#define URI_TEMPLATE_MAX_LENGTH 50 //buffer parametri uri template
#define X_WWW_FORM_URLENCODED_MAX_LEGTH 50 //buffer parametri x-www-form-urlencoded

#define API_NAME_MAX_LENGTH 25 //buffer API name
#define ACCOUNT_NAME_MAX_LENGTH 25 //buffer account name

//MMB class
class MMB {
	
	public:
		MMB(Client& client); //costructor
		~MMB(); //destroyer

		void setAccountName(char *account); //set account name
		void setAPIName(char *api); //set API name

		int run(); //execute API (make HTTP request)

		//lettura risposta
		int available();
		int read();
		void close();

		//aggiunta parametri
		void addQueryStringParameter(char *offset, char *value); //query string
		void addUriTemplateParameter(char *value); //uri template //DEVONO ESSERE INSERITI IN ORDINE
		void addXWWWFormUrlencodedParameter(char *offset, char *value); //x-www-form-urlencoded

		//---DEBUG PUBLIC---
		void printDataDebug();

	private:

		void buildApiURL(char *url); //build API URL
		void buildQueryStringParameter(char *queryString, char *offset, char *value); //costruisce il parametro queryString

		//---URLENCODE
		static char hexDigit(char c);
		char *urlencode(char *dst, char *src);

		//---DEBUG PRIVATE---
		void debugPrint(String msg);

		//---VARIABILI PRIVATE---
		HttpClient _http; //http client (SimpleHttpClient library)

		char _accountName[ACCOUNT_NAME_MAX_LENGTH]; //user account name
		char _apiName[API_NAME_MAX_LENGTH]; //user API name

		//buffer
		char _queryString[QUERY_STRING_MAX_LENGTH];
		char _uriTemplate[URI_TEMPLATE_MAX_LENGTH];
		char _xWWWFormUrlencoded[X_WWW_FORM_URLENCODED_MAX_LEGTH];

		//char _specialCharcathers[] = "$&+,/:;=?@ <>#%{}|~[]`"; //String containing chars you want encoded


};

#endif