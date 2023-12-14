#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H

#include <iostream>
#include <string>


class GPIO
{
	public:
		GPIO();
		GPIO(std::string pin);
	


		int gpioexport();
		int gpiounexport();
		int setdir(std::string dir);
		int setval(std::string val);
		int getval(std::string& val);
		std::string getNum();
	
	private:
		std::string Num;
	
};

#endif
