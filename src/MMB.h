/*
	MMB Library

	MANCA GESTIONE ERRORI CHIAMATA
*/

#ifndef MMB_H
#define MMB_H

#include "Arduino.h"
#include "Client.h"
#include "MMBHttpClient.h"

//HTTP CODE
#define MMB_HTTP_SUCCESS 0
#define MMB_HTTP_ERROR -1

//---INTERNAL CONFIGURATION
//debug
//#define DEBUG 1

#define MMB_API_HOSTNAME "api.mymicrobridge.com"

#define QUERY_STRING_INITIAL_SIZE 20 //buffer parametri query string
#define URI_TEMPLATE_INITIAL_SIZE 20 //buffer parametri uri template
#define X_WWW_FORM_URLENCODED_INITIAL_SIZE 1 //buffer parametri x-www-form-urlencoded

#define ACCOUNT_NAME_INITIAL_SIZE 20 //buffer account name
#define API_NAME_INITIAL_SIZE 20 //buffer API name

//MMB class
class MMB {
	
	public:

		MMB(Client& client); //costructor
		MMB(Client& client, int accountNameBufferSize, int apiNameBufferSize, int queryStringBufferSize, int uriTemplateBufferSize, int xWWWFormUrlencodedBufferSize); //costructor
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

		#ifdef DEBUG
			//---DEBUG PUBLIC---
			void printDataDebug();
		#endif


	private:

		void buildApiURL(char *url); //build API URL
		void buildUrlencodedParameter(char *queryString, char *offset, char *value); //costruisce il parametro queryString

		//---URLENCODE FUNCTION
		char *_specialCharacters = "$&+,/:;=?@ <>#%{}|~[]`";

		static char hex_digit(char c) {
			return "01234567890ABCDEF"[c & 0x0F];
		}

		void urlencode(char *dst,char *src); //esegue l'urlencode della stringa
		int countCharacterToUrlencode(char *str); 

		//---EXECUTE
		int execute(char *url); //segue la chiamata

		//---VARIABILI PRIVATE---
		MMBHttpClient _http; //http client (SimpleHttpClient library)

		char *_accountName; //user account name
		int _accountNameSize; //dimensione buffer

		char *_apiName; //user API name
		int _apiNameSize; //dimensione buffer

		//buffer QueryString
		char *_queryString;
		int _queryStringSize;

		//buffer UriTemplate
		char *_uriTemplate;
		int _uriTemplateSize;

		//buffer x-www-form-urlencoded parameter
		char *_xWWWFormUrlencoded;
		int _xWWWFormUrlencodedSize;


		#ifdef DEBUG
			//---DEBUG PRIVATE---
			void debugPrint(String msg);
		#endif


};

#endif