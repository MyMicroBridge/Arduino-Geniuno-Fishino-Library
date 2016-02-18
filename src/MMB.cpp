#include "Arduino.h"

#include "MMB.h"

//---PUBLIC---

//costructor and create _http client
MMB::MMB(Client& client): _http(client) {
	_client = &client; //save instance of client
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

	// if ((*_client).connect(server, 80)) {
	// 	debugPrint("\nSERVER: connected\n");
		
	// 	// invia la richiesta HTTP:
	// 	(*_client) << F("GET /asciilogo.txt HTTP/1.1\r\n");
	// 	(*_client) << F("Host: arduino.cc\r\n");
	// 	(*_client) << F("Connection: close\r\n");
	// 	(*_client).println();

	// 	debugPrint("SERVER: Request sent\n");
	// 	debugPrint("Finish!\n");

	// 	return 1; //connessione riuscita

	// } else {
	// 	// se la connessione non è riuscita:
	// 	debugPrint("connection failed\n");
	// 	debugPrint("Finish!\n");

	// 	return 0; //connessione non riuscita
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




//---PRIVATE---
char *MMB::buildResourceURL() {

	//concateno le varie parti dell'URL
	char *resource = "/"; //parto dalla root

	//concateno gli elementi fissi dell'URL
	resource = strcat(resource, _account);
	resource = strcat(resource, "/\0"); //aggiunto \0 per fix
	resource = strcat(resource, _api);

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