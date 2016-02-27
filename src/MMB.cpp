#include "Arduino.h"

#include "MMB.h"

//---PUBLIC---

MMB::MMB(Client& client): MMB(client, ACCOUNT_NAME_INITIAL_SIZE, API_NAME_INITIAL_SIZE, QUERY_STRING_INITIAL_SIZE, URI_TEMPLATE_INITIAL_SIZE, X_WWW_FORM_URLENCODED_INITIAL_SIZE) {}

//costructor and create _http client
MMB::MMB(Client& client, int accountNameBufferSize, int apiNameBufferSize, int queryStringBufferSize, int uriTemplateBufferSize, int xWWWFormUrlencodedBufferSize): _http(client) {

	//inizializzo i buffer

	//apiName
	_apiName = (char *) malloc(apiNameBufferSize * sizeof(char)); //alloco la memoria
	_apiNameSize = apiNameBufferSize; //salvo la dimensione

	//accountName
	_accountName = (char *) malloc(accountNameBufferSize * sizeof(char)); //alloco la memoria
	_accountNameSize = accountNameBufferSize; //salvo la dimensione

	//queryString
	_queryString = (char *) malloc(queryStringBufferSize * sizeof(char)); //alloco la memoria
	_queryStringSize = queryStringBufferSize; //salvo la dimensione
	_queryStringPos = 0; //posizione della stringa
	_queryString[0] = 0; //inserisco il carattere vuoto all'inizio

	//uriTemplate
	_uriTemplate = (char *) malloc(uriTemplateBufferSize * sizeof(char)); //alloco la memoria
	_uriTemplateSize = uriTemplateBufferSize; //salvo la dimensione
	_uriTemplatePos = 0; //posizione della stringa
	_uriTemplate[0] = 0; //inserisco il carattere vuoto all'inizio

	//uriTemplate
	_xWWWFormUrlencoded = (char *) malloc(xWWWFormUrlencodedBufferSize * sizeof(char)); //alloco la memoria
	_xWWWFormUrlencodedSize = xWWWFormUrlencodedBufferSize; //salvo la dimensione
	_xWWWFormUrlencodedPos = 0; //posizione della stringa
	_xWWWFormUrlencoded[0] = 0; //inserisco il carattere vuoto all'inizio
	
}

//destroyer
MMB::~MMB() {

	//libero la memoria allocata dinamicamente
	free(_accountName);
	free(_apiName);

	free(_queryString);
	free(_uriTemplate);
	free(_xWWWFormUrlencoded);

}

//---SET FUNZIONI INIZIALI
void MMB::setAccountName(char *account) { //account name

	#ifdef DEBUG
		debugPrint(F("\n SIZE OF _accountName: "));
		debugPrint(String(_accountNameSize));

		debugPrint(F("\n SIZE OF account: "));
		debugPrint(String(strlen(account) +1));
		debugPrint(F("\n"));
	#endif
	
	//se la dimensione del buffer è troppo piccola la realloco
	if (_accountNameSize < (strlen(account) +1)) {
		_accountName = (char *) realloc(_accountName, (strlen(account) +1) * sizeof(char));
		_accountNameSize = strlen(account) +1;
	}

	strcpy(_accountName, account);

}

void MMB::setAPIName(char *api) { //api name

	#ifdef DEBUG
		debugPrint(F("\n SIZE OF _apiName: "));
		debugPrint(String(_apiNameSize));

		debugPrint(F("\n SIZE OF api: "));
		debugPrint(String(strlen(api) +1));
		debugPrint(F("\n"));
	#endif
	
	//se la dimensione del buffer è troppo piccola la realloco
	if (_apiNameSize < (strlen(api) +1)) {
		_apiName = (char *) realloc(_apiName, (strlen(api) +1) * sizeof(char));
		_apiNameSize = strlen(api) +1;
	}

	strcpy(_apiName, api);
}

//---AGGIUNTA PARAMETRI API
void MMB::addQueryStringParameter(char *offset, char *value) { //query string

	#ifdef DEBUG
		debugPrint(F("\n SIZE OF _queryString: "));
		debugPrint(String(_queryStringSize));
		debugPrint(F("\n POSITION _queryString: "));
		debugPrint(String(_queryStringPos));

		debugPrint(F("\n SIZE OF data to insert: "));
		debugPrint(String(strlen(offset) + strlen(value) +1));
		debugPrint(F("\n"));
	#endif


	//se non è il primo parametro che inserisco
	if (_queryString[0] == 0) { //se query string è vuota

		if ((_queryStringSize - _queryStringPos) < (strlen(offset) + strlen(value) +2)) {

			//salvo il contenuto del buffer
			char tempBuffer[_queryStringSize];
			strcpy(tempBuffer, _queryString);

			//realloco il buffer e salvo la nuova dimensione
			_queryString = (char *) realloc(_queryString, (_queryStringSize + strlen(offset) + strlen(value) +2) * sizeof(char));
			_queryStringSize = _queryStringSize + strlen(offset) + strlen(value) +2;

			//ricopio il contenuto del buffer
			strcpy(_queryString, tempBuffer);

		}

		_queryStringPos = _queryStringPos + strlen(offset) + strlen(value) +1; //pre-salvo la nuova posizione
	} else {

		if ((_queryStringSize - _queryStringPos) < (strlen(offset) + strlen(value) +3)) {
			//salvo il contenuto del buffer
			char tempBuffer[_queryStringSize];
			strcpy(tempBuffer, _queryString);

			//realloco il buffer e salvo la nuova dimensione
			_queryString = (char *) realloc(_queryString, (_queryStringSize + strlen(offset) + strlen(value) +3) * sizeof(char));
			_queryStringSize = _queryStringSize + strlen(offset) + strlen(value) +3;

			//ricopio il contenuto del buffer
			strcpy(_queryString, tempBuffer);
		}

		strcat(_queryString, "&\0"); //aggiungo il carattere di separazione

		_queryStringPos = _queryStringPos + strlen(offset) + strlen(value) +2; //pre-salvo la nuova posizione
	}

	buildUrlencodedParameter(_queryString, offset, value); //aggiungo il parametro

}

void MMB::addUriTemplateParameter(char *value) { //uri template //DEVONO ESSERE INSERITI IN ORDINE

	#ifdef DEBUG
		debugPrint(F("\n SIZE OF _uriTemplate: "));
		debugPrint(String(_uriTemplateSize));
		debugPrint(F("\n POSITION _uriTemplate: "));
		debugPrint(String(_uriTemplatePos));

		debugPrint(F("\n SIZE OF data to insert: "));
		debugPrint(String(strlen(value) +1));
		debugPrint(F("\n"));
	#endif

	if (_uriTemplate[0] == 0) { //se query string è vuota

		if ((_uriTemplateSize - _uriTemplatePos) < (strlen(value) +1)) {

			//salvo il contenuto del buffer
			char tempBuffer[_uriTemplateSize];
			strcpy(tempBuffer, _uriTemplate);

			//realloco il buffer e salvo la nuova dimensione
			_uriTemplate = (char *) realloc(_uriTemplate, (_uriTemplateSize + strlen(value) +1) * sizeof(char));
			_uriTemplateSize = _uriTemplateSize + strlen(value) +1;

			//ricopio il contenuto del buffer
			strcpy(_uriTemplate, tempBuffer);

		}

		_uriTemplatePos = _uriTemplatePos + strlen(value); //pre-salvo la nuova posizione

	} else {

		if ((_uriTemplateSize - _uriTemplatePos) < (strlen(value) +2)) {

			//salvo il contenuto del buffer
			char tempBuffer[_uriTemplateSize];
			strcpy(tempBuffer, _uriTemplate);

			//realloco il buffer e salvo la nuova dimensione
			_uriTemplate = (char *) realloc(_uriTemplate, (_uriTemplateSize + strlen(value) +2) * sizeof(char));
			_uriTemplateSize = _uriTemplateSize + strlen(value) +2;

			//ricopio il contenuto del buffer
			strcpy(_uriTemplate, tempBuffer);

		}

		strcat(_uriTemplate, "/\0"); //aggiungo il carattere di separazione

		_uriTemplatePos = _uriTemplatePos + strlen(value) +1; //pre-salvo la nuova posizione
	}

	strcat(_uriTemplate, value); //aggiungo il carattere di separazione
	
}

void MMB::addXWWWFormUrlencodedParameter(char *offset, char *value) { //x-www-form-urlencoded

	#ifdef DEBUG
		debugPrint(F("\n SIZE OF _xWWWFormUrlencoded: "));
		debugPrint(String(_xWWWFormUrlencodedSize));
		debugPrint(F("\n POSITION _xWWWFormUrlencoded: "));
		debugPrint(String(_xWWWFormUrlencodedPos));

		debugPrint(F("\n SIZE OF data to insert: "));
		debugPrint(String(strlen(offset) + strlen(value) +1));
		debugPrint(F("\n"));
	#endif


	//se non è il primo parametro che inserisco
	if (_xWWWFormUrlencoded[0] == 0) { //se query string è vuota

		if ((_xWWWFormUrlencodedSize - _xWWWFormUrlencodedPos) < (strlen(offset) + strlen(value) +2)) {

			//salvo il contenuto del buffer
			char tempBuffer[_xWWWFormUrlencodedSize];
			strcpy(tempBuffer, _xWWWFormUrlencoded);

			//realloco il buffer e salvo la nuova dimensione
			_xWWWFormUrlencoded = (char *) realloc(_xWWWFormUrlencoded, (_xWWWFormUrlencodedSize + strlen(offset) + strlen(value) +2) * sizeof(char));
			_xWWWFormUrlencodedSize = _xWWWFormUrlencodedSize + strlen(offset) + strlen(value) +2;

			//ricopio il contenuto del buffer
			strcpy(_xWWWFormUrlencoded, tempBuffer);

		}

		_xWWWFormUrlencodedPos = _xWWWFormUrlencodedPos + strlen(offset) + strlen(value) +1; //pre-salvo la nuova posizione
	} else {

		if ((_xWWWFormUrlencodedSize - _xWWWFormUrlencodedPos) < (strlen(offset) + strlen(value) +3)) {
			//salvo il contenuto del buffer
			char tempBuffer[_xWWWFormUrlencodedSize];
			strcpy(tempBuffer, _xWWWFormUrlencoded);

			//realloco il buffer e salvo la nuova dimensione
			_xWWWFormUrlencoded = (char *) realloc(_xWWWFormUrlencoded, (_xWWWFormUrlencodedSize + strlen(offset) + strlen(value) +3) * sizeof(char));
			_xWWWFormUrlencodedSize = _xWWWFormUrlencodedSize + strlen(offset) + strlen(value) +3;

			//ricopio il contenuto del buffer
			strcpy(_xWWWFormUrlencoded, tempBuffer);
		}

		strcat(_xWWWFormUrlencoded, "&\0"); //aggiungo il carattere di separazione

		_xWWWFormUrlencodedPos = _xWWWFormUrlencodedPos + strlen(offset) + strlen(value) +2; //pre-salvo la nuova posizione
	}

	buildUrlencodedParameter(_xWWWFormUrlencoded, offset, value); //aggiungo il parametro
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
	#ifdef DEBUG
		debugPrint(F("Running..............."));
	#endif

	//creo e inizializzo url con size minima
	if ((_uriTemplate[0] != 0) && (_queryString[0] != 0)) {
		char url[_accountNameSize + 1 + _apiNameSize +1 + _uriTemplatePos +1 + _queryStringPos + 2 +1];

		url[0] = 0;

		buildApiURL(url);
		return execute(url);
	
	} else if (_uriTemplate[0] != 0) {
		char url[_accountNameSize + 1 + _apiNameSize +1 + _uriTemplatePos +1 +1];

		url[0] = 0;

		buildApiURL(url);
		return execute(url);

	}  else if (_queryString[0] != 0) {
		char url[_accountNameSize + 1 + _apiNameSize +1 + _queryStringPos + 2 +1];

		url[0] = 0;

		buildApiURL(url);
		return execute(url);
	
	} else {
		char url[_accountNameSize + 1 + _apiNameSize +1 +1];

		url[0] = 0;

		buildApiURL(url);
		return execute(url);
	}

}



//---PRIVATE---


//---EXECUTE
int MMB::execute(char *url) {

	#ifdef DEBUG
		debugPrint(F("\nURL: "));
		debugPrint(url);
		debugPrint(F("\n"));

		debugPrint(F("\nURL SIZE: "));
		debugPrint(String(strlen(url) +1));
		debugPrint(F("\n"));
	#endif

	//status code
	int status = _http.get(MMB_API_HOSTNAME, url);

	if (status == 0) {

		#ifdef DEBUG
			debugPrint(F("OK\n"));
			status = _http.responseStatusCode();
			debugPrint(F("STATUS CODE: "));
			debugPrint(String(status));
		#endif

		//skip ResponseHeader
		_http.skipResponseHeaders();

	} else {

		#ifdef DEBUG
			debugPrint(F("ERROR\n"));
			debugPrint(F("ERROR: "));
			debugPrint(String(status));
		#endif

		return status; //ritorno il codice di errore
	}

}

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
void MMB::buildUrlencodedParameter(char *queryString, char *offset, char *value) {

	//inserisco il parametro 
	strcat(queryString, offset);
	strcat(queryString, "=\0");
	strcat(queryString, value);
}


#ifdef DEBUG
	//---DEBUG---
	void MMB::printDataDebug() {
		Serial.println();
		Serial.println(F("---------------DEBUG---------------"));

		Serial.print(F("BUFFER ACCOUNT NAME: "));
		Serial.println(_accountName);

		Serial.print(F("BUFFER API NAME: "));
		Serial.println(_apiName);

		Serial.print(F("BUFFER QUERY STRING PARAMS: "));
		Serial.println(_queryString);

		Serial.print(F("BUFFER URI TEMPLATE PARAMS: "));
		Serial.println(_uriTemplate);

		Serial.print(F("BUFFER X-WWW-FORM-URLENCODED PARAMS: "));
		Serial.println(_xWWWFormUrlencoded);

		Serial.println(F("---------------DEBUG---------------"));
		Serial.println();
	}

	void MMB::debugPrint(String msg) {
		Serial.print(msg);

	}
#endif