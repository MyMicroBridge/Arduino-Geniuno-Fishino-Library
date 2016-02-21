/*
	MMB Library
*/

#ifndef MMBJSONPARSER_H
#define MMBJSONPARSER_H

#include "Arduino.h"
#include <ArduinoJson.h>

//debug
#define DEBUG 1


class MMBJsonParser {

	public:

		MMBJsonParser(String *str);
		~MMBJsonParser(); //destroyer

		//---GET FUNCTION
		int getStatusCode();


	private:

		//---DEBUG PRIVATE---
		void debugPrint(String msg);

		//buffer Json
		StaticJsonBuffer<200> _jsonBuffer;

		//json object
		JsonObject *_json;




};




#endif