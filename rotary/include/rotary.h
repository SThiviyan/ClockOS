#pragma once

#include <iostream>
#include <string>
#include "../../rotary/lib/GPIO.h"
#include <functional>


class rotaryButton
{


	public:	

	rotaryButton(std::string CLKPIN, std::string DTPIN, std::string SWPIN);
	~rotaryButton();	

	int getPosition();
	void executecallbackfunc(); //undefined func

	void automaticPosDetection(bool On);
	void SetPressCallback(std::function<void ()> Callback);


	private:
	std::string getCLKval();
	std::string getDTval();
	std::string getSWval();

	std::function<void ()> callbackfunc;
	
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
