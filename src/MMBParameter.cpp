#include "Arduino.h"
#include "MMBParameter.h"

//---PUBLIC---

//costruttori

MMBParameter::MMBParameter(int type, char *offset, char *value): MMBParameter(type, offset, 0, value){} //constructor

MMBParameter::MMBParameter(int type, int position, char *value): MMBParameter(type, "\0", position, value){} //constructor

MMBParameter::~MMBParameter() {
	
}


//get method
int MMBParameter::getType() {
	return _type;
}

char *MMBParameter::getOffset() {
	return _offset;
}

int MMBParameter::getPosition() {
	return _position;
}

char *MMBParameter::getValue() {
	return _value;
}

//---PRIVATE---

//costruttore privato usato per creare l'oggetto MMBParameter
MMBParameter::MMBParameter(int type, char *offset, int position, char *value) {

	_type = type;
	_offset = offset;
	_position = position;
	_value = value;

}