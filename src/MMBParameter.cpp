#include "Arduino.h"
#include "MMBParameter.h"

//---PUBLIC---

//costruttori
MMBParameter::MMBParameter(const int type, const char *offset); //constructor

MMBParameter::MMBParameter(const int type, const char *offset, const char *value); //constructor

MMBParameter::MMBParameter(const int type, const int position); //constructor

MMBParameter::MMBParameter(const int type, const int position, const char *value); //constructor

//salvo il valore del parametro
MMBParameter::setValue(const char *value) {
	_value = value;
}