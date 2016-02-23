/*
	MMBJsonParser Library

*/

#ifndef MMBJSONPARSER_H
#define MMBJSONPARSER_H

#include "Arduino.h"
#include <ArduinoJson.h>

//debug
//#define DEBUG 1

#define JSON_MESSAGE_INITIAL_SIZE 130

//---STATUS CODE
//bad request 1xx
#define MMBJSON_USERNAME_NOT_FOUND 100
#define MMBJSON_API_NOT_FOUND 101
#define MMBJSON_PARAMETER_NOT_FOUND 102

//ok 2xx
#define MMBJSON_OK 200

//permission error 3xx
#define MMBJSON_HTTPS_CALL_NOT_ALLOWED 300
#define MMBJSON_DAILY_API_CALLS_LIMIT_EXCEEDED 301
#define MMBJSON_HOURLY_API_CALLS_LIMIT_EXCEEDED 302
#define MMBJSON_DATA_LIMIT_EXCEEDED 303
#define MMBJSON_API_CALLS_MUST_BE_PERFORMED_UNDER_HTTPS 304

//service error 4xx
#define MMBJSON_INTERNAL_SERVICE_ERROR 400

//server error 5xx
#define MMBJSON_INTERNAL_SERVER_ERROR 500

//response error 6xx
#define MMBJSON_INTERNAL_SOURCE_ERROR 600

//response error 7xx
#define MMBJSON_INTERNAL_RESPONSE_FORMAT_ERROR 700


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

		JsonVariant getData(char *key);
		JsonVariant getData(char *key, char *nspace);

		JsonVariant getErrors(int index, char *nspace);

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