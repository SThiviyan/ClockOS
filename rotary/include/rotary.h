#pragma once

#include <iostream>
#include <string>
#include "../../rotary/lib/GPIO.h"

typedef void (*PressCallback)();

class rotaryButton
{


	public:	

	rotaryButton(std::string CLKPIN, std::string DTPIN, std::string SWPIN);
	~rotaryButton();	

	int getPosition();
	void automaticPosDetection(bool On);
	void SetPressCallback(PressCallback callback);


	private:
	std::string getCLKval();
	std::string getDTval();
	std::string getSWval();

	PressCallback Pcb;
	
	void determinePos();
	bool autoPos;

	int pos;	
	std::string CLKPIN;
	std::string DTPIN;
	std::string SWPIN;

	GPIO CLK;
	GPIO DT;
	GPIO SW;

};
