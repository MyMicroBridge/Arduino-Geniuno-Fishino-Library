/*
	MMBJsonParser Library
	
	MANCA LA GESTIONE DEGLI ERRORI

*/

#ifndef MMBJSONPARSER_H
#define MMBJSONPARSER_H

#include "Arduino.h"
#include <ArduinoJson.h>

#define JSON_MESSAGE_INITIAL_SIZE 130
//#define JSON_BUFFER_SIZE 200;

//debug
//#define DEBUG 1

//costanti per parsing JSON MMB
#define API_EXECUTED_SUCCESFULLY 200

//definisco gli errori


class MMBJsonParser {

	public:

		MMBJsonParser();
		MMBJsonParser(int dim);
		~MMBJsonParser(); //destroyer


		//---PASE FUNCTION
		void parseJson(char *message);
		void parseJson(String message);
		void parseJson();

		//---GET FUNCTION
		int getStatusCode();
		const char *getErrorMessage();
		const char *getAPIName();

		JsonVariant getData(char *key);
		JsonVariant getData(char *key, char *nspace);

		//---ADD CHARACTER
		void addCharacter(char c);

		//---CHECK IF PARSING IS SUCCESSED
		uint8_t success();



	private:

		//buffer messaggio
		char *_jsonMessage;
		int _index = 0;

		//buffer Json
		StaticJsonBuffer<200> _jsonBuffer;

		//json object
		JsonObject *_json;

		uint8_t _parseSuccess;

		#ifdef DEBUG
			//---DEBUG PRIVATE---
			void debugPrint(String msg);
		#endif


};




#endif