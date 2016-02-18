#include "Arduino.h"
#include "MMBParameter.h"

//---PUBLIC---

//costruttori
MMBParameter::MMBParameter(const int type, const char *offset): MMBParameter(type, offset, 0, "\0"){} //constructor

MMBParameter::MMBParameter(const int type, const char *offset, const char *value): MMBParameter(type, offset, 0, value){} //constructor

MMBParameter::MMBParameter(const int type, const int position): MMBParameter(type, "\0", position, "\0"){} //constructor

MMBParameter::MMBParameter(const int type, const int position, const char *value): MMBParameter(type, "\0", position, value){} //constructor

//salvo il valore del parametro
void MMBParameter::setValue(const char *value) {
	_value = value;
}

//---PRIVATE---

//costruttore privato usato per creare l'oggetto MMBParameter
MMBParameter::MMBParameter(const int type, const char *offset, const int position, const char *value) {

	_type = type;
	_offset = offset;
	_position = position;
	_value = value;

}