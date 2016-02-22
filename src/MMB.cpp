#include "Arduino.h"

#include "MMB.h"

//---PUBLIC---

//costructor and create _http client
MMB::MMB(Client& client): _http(client) {
	
	//inizializzo i buffer
	_accountName[0] = 0;
	_apiName[0] = 0;

	_queryString[0] = 0;
	_uriTemplate[0] = 0;
	_xWWWFormUrlencoded[0] = 0;
}

//destroyer
MMB::~MMB() {

}

//---SET FUNZIONI INIZIALI
void MMB::setAccountName(char *account) { //account name
	strcpy(_accountName, account);
}

void MMB::setAPIName(char *api) { //api name
	strcpy(_apiName, api);
}

//---AGGIUNTA PARAMETRI API
void MMB::addQueryStringParameter(char *offset, char *value) { //query string

	//se non è il primo parametro che inserisco
	if (_queryString[0] != 0) { //se query string è vuota
		strcat(_queryString, "&\0");
	}

	buildQueryStringParameter(_queryString, offset, value);

}

void MMB::addUriTemplateParameter(char *value) { //uri template //DEVONO ESSERE INSERITI IN ORDINE
	strcat(_uriTemplate, value);
}

void MMB::addXWWWFormUrlencodedParameter(char *offset, char *value) { //x-www-form-urlencoded

}

//---LETTURA DELLA RISPOSTA
int MMB::available() {
	return _http.available();
}

int MMB::read() {
	return _http.read();
}

void MMB::close() {
	return _http.stop();
}

//---ESECUZIONE API (CHIAMATA HTTP)
int MMB::run() {
	debugPrint("Running...............");

	//creo e inizializzo url
	char url[API_URL_SIZE];
	url[0] = 0;

	buildApiURL(url);

	debugPrint("\nURL: ");
	debugPrint(url);
	debugPrint("\n");


	//status code
	int status = _http.get(MMB_API_HOSTNAME, url);

	if (status == 0) {

		debugPrint("OK\n");
		status = _http.responseStatusCode();
		debugPrint("STATUS CODE: " + String(status));

		//skip ResponseHeader
		_http.skipResponseHeaders();

	} else {
		debugPrint("ERROR\n");
		debugPrint("ERROR: " + String(status));

		return status; //ritorno il codice di errore
	}

}



//---PRIVATE---

//costruisce l'url della risorsa (API) con i parametri
void MMB::buildApiURL(char * url) {

	//---BASE URL
	strcat(url, "/");
	strcat(url, _accountName);
	strcat(url, "/");
	strcat(url, _apiName);

	//---AGGIUNTA URI TEMPLATE
	if (_uriTemplate[0] != 0) {
		strcat(url, "/");
		strcat(url, _uriTemplate);
	}

	//---AGGIUNTA QUERY STRING
	if (_queryString[0] != 0) {
		strcat(url, "/?");
		strcat(url, _queryString);
	}

}

//costruisce e restituisce un parametro query string
void MMB::buildQueryStringParameter(char *queryString, char *offset, char *value) {

	//inserisco il parametro 
	strcat(queryString, offset);
	strcat(queryString, "=\0");
	strcat(queryString, value);
}


//---URLENCODE
// static char MMB::hexDigit(char c) {
// 	return "01234567890ABCDEF"[c & 0x0F];
// }

// char *MMB::urlencode(char *dst, char *src) {
	
// 	char *d = dst;
  	
//   	while (c = *src++) {
//   		if (strchr(specials,c)) {  

//   			*d++ = '%';
// 			*d++ = hex_digit(c >> 4);
// 			*d++ = hex_digit(c);
// 		} else {
// 			*d++ = c;
// 		}
// 	}
	
// 	return dst;
// }


//---DEBUG---
void MMB::printDataDebug() {
	Serial.println();
	Serial.println("---------------DEBUG---------------");

	Serial.print("BUFFER ACCOUNT NAME: ");
	Serial.println(_accountName);

	Serial.print("BUFFER API NAME: ");
	Serial.println(_apiName);

	Serial.print("BUFFER QUERY STRING PARAMS: ");
	Serial.println(_queryString);

	Serial.print("BUFFER URI TEMPLATE PARAMS: ");
	Serial.println(_uriTemplate);

	Serial.print("BUFFER X-WWW-FORM-URLENCODED PARAMS: ");
	Serial.println(_xWWWFormUrlencoded);

	Serial.println("---------------DEBUG---------------");
	Serial.println();
}

void MMB::debugPrint(String msg) {

	if (DEBUG) {
		Serial.print(msg);
	}

}