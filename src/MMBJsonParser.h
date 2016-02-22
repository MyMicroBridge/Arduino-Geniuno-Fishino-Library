/*
	MMB Library
*/

#ifndef MMBJSONPARSER_H
#define MMBJSONPARSER_H

#include "Arduino.h"
#include <ArduinoJson.h>

#define JSON_MESSAGE_SIZE 200
//#define JSON_BUFFER_SIZE 200;

//debug
#define DEBUG 1


class MMBJsonParser {

	public:

		MMBJsonParser();
		~MMBJsonParser(); //destroyer


		//---PASE FUNCTION
		void parseJson(char *message);


		//---GET FUNCTION
		int getStatusCode();

		JsonVariant getValue(char *key);


	private:

		//---DEBUG PRIVATE---
		void debugPrint(String msg);

		char _jsonMessage[JSON_MESSAGE_SIZE];

		//buffer Json
		StaticJsonBuffer<200> _jsonBuffer;

		//json object
		JsonObject *_json;




};




#endif