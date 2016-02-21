#include "Arduino.h"

#include "MMBJsonParser.h"
	
//---PUBLIC---

//costruttore
MMBJsonParser::MMBJsonParser(String *str) {

	//String message = str;

	(*str).replace("\n", "");
	(*str).replace("\t", "");
	(*str).replace(" ", "");

	debugPrint("----MESSAGE----\n");

	Serial.print(*str);

	debugPrint("\n");

	//debugPrint("OK");

	//creo json object
	_json = &_jsonBuffer.parseObject((*str));


	if (!(*_json).success()) {
		debugPrint("_json parseObject() failed\n");
	}

}

//destroyer
MMBJsonParser::~MMBJsonParser() {

}

//---GET FUNCTION
int MMBJsonParser::getStatusCode() {

	//int value = (*_json)["responses"][0]["status"]["code"];

	//debugPrint("STATUS_CODE_INTERNAL");
	//debugPrint(String(value));

	return (*_json)["responses"][0]["status"]["code"];
}


//---DEBUG---
void MMBJsonParser::debugPrint(String msg) {

	if (DEBUG) {
		Serial.print(msg);
	}

}