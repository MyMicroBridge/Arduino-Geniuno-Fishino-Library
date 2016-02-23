/*
	MMB Library
*/

#ifndef MMBJSONPARSER_H
#define MMBJSONPARSER_H

#include "Arduino.h"
#include <ArduinoJson.h>

#define JSON_MESSAGE_INITIAL_SIZE 130
//#define JSON_BUFFER_SIZE 200;

//debug
#define DEBUG 1


class MMBJsonParser {

	public:

		MMBJsonParser();
		~MMBJsonParser(); //destroyer


		//---PASE FUNCTION
		void parseJson(char *message);
		void parseJson(String message);
		void parseJson();

		//---GET FUNCTION
		int getStatusCode();

		//---ADDE
		void addCharacter(char c);

		JsonVariant getValue(char *key);


	private:

		//---DEBUG PRIVATE---
		void debugPrint(String msg);

		char _jsonMessage[JSON_MESSAGE_INITIAL_SIZE];

		int _index = 0;

		//buffer Json
		StaticJsonBuffer<200> _jsonBuffer;

		//json object
		JsonObject *_json;


};




#endif