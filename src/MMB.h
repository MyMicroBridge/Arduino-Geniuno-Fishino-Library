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

// #define API_URL_INITIAL_SIZE 60 //buffer API URL (DA RIMUOVERE)

#define QUERY_STRING_INITIAL_SIZE 20 //buffer parametri query string
#define URI_TEMPLATE_INITIAL_SIZE 20 //buffer parametri uri template
// #define X_WWW_FORM_URLENCODED_INITIAL_SIZE 1 //buffer parametri x-www-form-urlencoded

#define ACCOUNT_NAME_INITIAL_SIZE 20 //buffer account name
#define API_NAME_INITIAL_SIZE 20 //buffer API name

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
		// void addXWWWFormUrlencodedParameter(char *offset, char *value); //x-www-form-urlencoded

		#ifdef DEBUG
			//---DEBUG PUBLIC---
			void printDataDebug();
		#endif


	private:

		void buildApiURL(char *url); //build API URL
		void buildQueryStringParameter(char *queryString, char *offset, char *value); //costruisce il parametro queryString

		//---EXECUTE
		int execute(char *url); //segue la chiamata


		//---RESIZE BUFFER
		char *resizeBuffer(char *buffer, int oldDim, int newDim);

		//---URLENCODE
		// static char hexDigit(char c);
		// char *urlencode(char *dst, char *src);

		//---VARIABILI PRIVATE---
		HttpClient _http; //http client (SimpleHttpClient library)

		char *_accountName; //user account name
		int _accountNameSize; //dimensione buffer

		char *_apiName; //user API name
		int _apiNameSize; //dimensione buffer

		//buffer QueryString
		char *_queryString;
		int _queryStringSize;
		int _queryStringPos;

		//bufferUriTemplate
		char *_uriTemplate;
		int _uriTemplateSize;
		int _uriTemplatePos;

		//char *_xWWWFormUrlencoded;

		//char _specialCharcathers[] = "$&+,/:;=?@ <>#%{}|~[]`"; //String containing chars you want encoded


		#ifdef DEBUG
			//---DEBUG PRIVATE---
			void debugPrint(String msg);
		#endif


};

#endif