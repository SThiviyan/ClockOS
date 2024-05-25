#include <iostream>
#include "../include/rotary.h"
#include <unistd.h>


rotaryButton::rotaryButton(std::string CLKPIN, std::string DTPIN, std::string SWPIN)
{       
	this->CLKPIN = CLKPIN;
	this->DTPIN = DTPIN;
	this->SWPIN = SWPIN;

	
	this->CLK = GPIO(this->CLKPIN);
	this->DT = GPIO(this->DTPIN);
	this->SW = GPIO(this->SWPIN);

	this->CLK.gpioexport();
	this->DT.gpioexport();
	this->SW.gpioexport();

	this->CLK.setdir("in");
	this->DT.setdir("in");
	this->SW.setdir("in");


}

rotaryButton::~rotaryButton()
{
	this->autoPos = false;

	this->CLK.gpiounexport();
	this->DT.gpiounexport();
	this->SW.gpiounexport();
}


void rotaryButton::SetPressCallback(std::function<void ()> Callback)
{
	this->callbackfunc = Callback;
}


void rotaryButton::automaticPosDetection(bool On)
{
	this->autoPos = On;

	while(this->autoPos)
	{
		determinePos();

		if(this->callbackfunc)
			this->callbackfunc();
	}
}


int rotaryButton::getPosition()
{
	return this->pos;
}



void rotaryButton::determinePos()
{	
	std::string clkLastState = this->getCLKval();
	
	int counter = 0;

	while(this->autoPos)
	{
		std::string clkState = this->getCLKval();
		std::string dtState = this->getDTval();

		if(clkState != clkLastState)
		{
			if(dtState == clkState)
			{
				counter++;
			}
			else
			{
				counter--;
			}

			clkLastState = clkState;
		}
	
		
		this->pos = counter;
		//std::cout << "counter:" << this->pos << std::endl;


		usleep(1000);
	}
}

std::string rotaryButton::getCLKval()
{
	std::string temp;
	CLK.getval(temp);
	return temp;
}


std::string rotaryButton::getDTval()
{
	std::string temp;
	DT.getval(temp);
	return temp;
}

std::string rotaryButton::getSWval()
{
	std::string temp;
	SW.getval(temp);
	return temp;
}
