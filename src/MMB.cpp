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
void MMB::setAccountName(char *account) {
	_account = account;
}

//save API name
void MMB::setAPIName(char *api) {
	_api = api;
}

//execute API
int MMB::run() {
	debugPrint("Running...............");

	//costruisco l'URL della risorsa da chiamare
	buildResourceURL();

	debugPrint("\nRESOURCE: ");
	debugPrint(_resource);
	debugPrint("\n");

	//status code
	// int status = _http.get(MMB_API_HOSTNAME, resource);

	// if (status == 0) {
	// 	debugPrint("OK\n");
	// 	status = _http.responseStatusCode();
	// 	debugPrint("STATUS CODE: " + String(status));

	// 	//skip ResponseHeader
	// 	_http.skipResponseHeaders();


	// } else {
	// 	debugPrint("ERROR\n");
	// 	debugPrint("ERROR: " + String(status));

	// 	return status; //ritorno il codice di errore
	// }

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
void MMB::buildResourceURL() {

	//inizializzo _resource
	_resource[0] = '/';
	_resource[1] = 0;

	//concateno gli elementi fissi dell'URL
	strcat(_resource, _account);
	strcat(_resource, "/\0"); //aggiunto \0 per fix
	strcat(_resource, _api);

	debugPrint("hey");

	// if (_pos != 0) { //esistono parametri da valutare

	// 	char uri_template[_pos][];

	// 	//inizializzo uritemplate
	// 	for (int i = 0; i < _pos; i++) {
	// 		uri_template[i] = "\0";
	// 	}

	// 	char *query_string = "/?\0";

	// 	debugPrint(String("\n\nQUERY STRING: "));
	// 	//debugPrint(query_string);
	// 	debugPrint("\n\n");

	// 	for (int i = 0; i < _pos; i++) { //scorro tutti i parametri

	// 		if ((*_params[i]).getType() == MMB_PARAMETER_X_WWW_FORM_URLENCODED) {
	// 			uri_template[(*_params[i]).getPosition()] = (*_params[i]).getValue();
			
	// 		} else if ((*_params[i]).getType() == MMB_PARAMETER_QUERY_STRING) {

	// 			if (query_string[0] == '/') { //se query string è vuota

	// 				query_string = strcat(query_string, buildQueryStringParameter((*_params[i]).getOffset(), (*_params[i]).getValue()));
					

	// 			} else { //altrimenti concateno

	// 				query_string = strcat(query_string, "&\0");
	// 				query_string = strcat(query_string, (*_params[i]).getOffset());
	// 				query_string = strcat(query_string, "=\0");
	// 				query_string = strcat(query_string, (*_params[i]).getValue());
	// 			}

	// 		}
	// 	}

	// 	debugPrint("\nQUERY STRING: ");
	// 	debugPrint(query_string);
	// 	debugPrint("\n");

	// 	char *uri_template_string = "\0";

	// 	for (int i = 0; i < _pos; i++) {

	// 		if (uri_template[i][0] != '\0') {
	// 			uri_template_string = strcat(uri_template_string, "/");
	// 			uri_template_string = strcat(uri_template_string, uri_template[i]);
	// 		}

	// 	}

	// 	//concateno resource con uri_template_string
	// 	resource = strcat(resource, uri_template_string);

	// 	se query_string non è vuota la concateno
	// 	if (query_string[0] != '/') {
	// 		resource = strcat(resource, query_string);
	// 	}

	// }

}

//costruisce e restituisce un parametro query string
void MMB::buildQueryStringParameter(char *offset, char *value) {

	// char *parameter;

	// parameter = strcat(offset, "=");
	// parameter = strcat(parameter, value);

	// debugPrint("\n\nPARAMETER:  ");
	// debugPrint(parameter);
	// debugPrint("\n\n");

	// //return parameter;

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