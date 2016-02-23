#include "Arduino.h"

#include "MMBJsonParser.h"
	
//---PUBLIC---

//costruttore
MMBJsonParser::MMBJsonParser():MMBJsonParser(JSON_MESSAGE_INITIAL_SIZE) {}

MMBJsonParser::MMBJsonParser(int dim) {

	_jsonMessage = (char *) malloc(dim * sizeof(char)); //alloco la memoria

	//inserisco il terminatore in _jsonMessage
	_jsonMessage[0] = 0;

	//azzero l'indice
	_index = 0;

	//inizializzo il siccesso del parsing a 0
	_parseSuccess = 0; //ci sono errori
}

//destroyer
MMBJsonParser::~MMBJsonParser() {
	free(_jsonMessage);
}


//---PARSE FUNCTION
void MMBJsonParser::parseJson(char *message) { //devono essere già stati eliminati \n \t e spazi
	
	#ifdef DEBUG
		debugPrint(F("\n\n---MESSAGE TO PARSE---\n\n"));
		debugPrint(message);
	#endif

	strcpy(_jsonMessage, message);

	//creo json object
	_json = &_jsonBuffer.parseObject(_jsonMessage);


	if (!(*_json).success()) {
		#ifdef DEBUG
			debugPrint(F("_json parseObject() failed\n"));
		#endif

		_parseSuccess = 0;

	} else {
		_parseSuccess = 1;
	}
}

void MMBJsonParser::parseJson(String message) { //elimino \n \t e spazi
	
	message.replace("\n", "");
	message.replace("\t", "");
	message.replace(" ", "");

	#ifdef DEBUG
		debugPrint(F("\n\n---MESSAGE TO PARSE---\n\n"));
		debugPrint(message);
	#endif



	message.toCharArray(_jsonMessage, JSON_MESSAGE_INITIAL_SIZE);

	//strcpy(_jsonMessage, message);
	//strcat(_jsonMessage, "\0");

	//creo json object
	_json = &_jsonBuffer.parseObject(_jsonMessage);


	if (!(*_json).success()) {
		#ifdef DEBUG
			debugPrint(F("_json parseObject() failed\n"));
		#endif
		
		_parseSuccess = 0;

	} else {
		_parseSuccess = 1;
	}
}

void MMBJsonParser::parseJson() { //elimino \n \t e spazi

	#ifdef DEBUG
		debugPrint(F("\n\n---MESSAGE TO PARSE---\n\n"));
		debugPrint(_jsonMessage);
	#endif

	//creo json object
	_json = &_jsonBuffer.parseObject(_jsonMessage);


	if (!(*_json).success()) {
		#ifdef DEBUG
			debugPrint(F("_json parseObject() failed\n"));
		#endif
		
		_parseSuccess = 0;

	} else {
		_parseSuccess = 1;
	}
}


//---GET FUNCTION
int MMBJsonParser::getStatusCode() {
	return (*_json)["responses"][0]["status"]["code"];
}

const char *MMBJsonParser::getErrorMessage() {
	return (*_json)["responses"][0]["status"]["message"];
}

const char *MMBJsonParser::getAPIName() {
	return (*_json)["responses"][0]["status"]["api"];
}

JsonVariant MMBJsonParser::getData(char *key) {
	return getData(key, "default");
}

JsonVariant MMBJsonParser::getData(char *key, char *nspace) {
	return (*_json)["responses"][0]["data"][nspace][key];
}



//---ADD FUNCTION
void MMBJsonParser::addCharacter(char c) {

	if (c == '\n'  || c == '\t' || c == ' ') {
		return;
	}

	_jsonMessage[_index++] = c;
	_jsonMessage[_index] = 0;

}

//---SUCCESS
uint8_t MMBJsonParser::success() {
	return _parseSuccess;
}

#ifdef DEBUG
	//---DEBUG---
	void MMBJsonParser::debugPrint(String msg) {
		Serial.print(msg);
	}
#endif


