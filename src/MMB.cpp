#include "Arduino.h"

#include "MMB.h"

//---PUBLIC---

//costructor and create _http client
MMB::MMB(Client& client): _http(client) {
	_client = &client; //save instance of client

	_pos = 0;
}

//destroyer
MMB::~MMB() {

}

//save account name
void MMB::setAccountName(const char *account) {
	_account = account;
}

//save API name
void MMB::setAPIName(const char *api) {
	_api = api;
}

//execute API
int MMB::run() {
	debugPrint("Running...............");

	//costruisco l'URL della risorsa da chiamare
	char *resource = buildResourceURL();

	debugPrint("\nRESOURCE: ");
	debugPrint(resource);
	debugPrint("\n");

	//status code
	int status = _http.get(MMB_API_HOSTNAME, resource);

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

//lettura risposta
int MMB::available() {
	return _http.available();
}

int MMB::read() {
	return _http.read();
}

void MMB::close() {
	return _http.stop();
}


//aggiunta del parametro dell'API
int MMB::addParameter(MMBParameter& parameter) { //DA MODIFICARE E INSERIRE LA POSSIBILITA' DI GESTIRE INSERIMENTO E RIMOZIONE, RICERCA ...

	if (_pos < MAX_PARAMETER) {
		_params[_pos] = &parameter;

		_pos++;

		return 1;
	} else {
		return 0;
	}

}



//---PRIVATE---

//costruisce l'url della risorsa (API) con i parametri
char *MMB::buildResourceURL() {

	//concateno le varie parti dell'URL
	char *resource = "/"; //parto dalla root

	//concateno gli elementi fissi dell'URL
	resource = strcat(resource, _account);
	resource = strcat(resource, "/\0"); //aggiunto \0 per fix
	resource = strcat(resource, _api);

	if (_pos != 0) { //esistono parametri da valutare

		const char *uri_template[_pos];
		char *query_string = "/\0";

		for (int i = 0; i < _pos; i++) { //scorro tutti i parametri

			if ((*_params[i]).getType() == MMB_PARAMETER_X_WWW_FORM_URLENCODED) {
				uri_template[(*_params[i]).getPosition()] = (*_params[i]).getValue();
			
			} else if ((*_params[i]).getType() == MMB_PARAMETER_QUERY_STRING) {

				if (query_string[0] == '/') { //se query string è vuota

					query_string = strcat(query_string, (*_params[i]).getOffset());
					query_string = strcat(query_string, "=\0");
					query_string = strcat(query_string, (*_params[i]).getValue());

				} else { //altrimenti concateno

					query_string = strcat(query_string, "&\0");
					query_string = strcat(query_string, (*_params[i]).getOffset());
					query_string = strcat(query_string, "=\0");
					query_string = strcat(query_string, (*_params[i]).getValue());
				}

			}
		}
	}

	return resource;

}


//---DEBUG---
void MMB::printDataDebug() {
	Serial.println();
	Serial.println("---------------DEBUG---------------");
	Serial.print("ACCOUNT NAME: ");
	Serial.println(_account);
	Serial.print("API NAME: ");
	Serial.println(_api);
	Serial.println("---------------DEBUG---------------");
	Serial.println();
}

void MMB::debugPrint(String msg) {

	if (DEBUG) {
		Serial.print(msg);
	}

}