

#include "GPIO.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

GPIO::GPIO()
{
	
	this->Num=21;
}

GPIO::GPIO(std::string pin)
{
	this->Num=pin;
}


int GPIO::gpioexport()
{
	std::string export_str = "/sys/class/gpio/export";
	std::ofstream gpioExport(export_str.c_str());
	if(!gpioExport)
	{
		std::cout << "GPIO" << this->Num << " Export failed!"; 
		return -1;
	}

	gpioExport << this->Num;
	gpioExport.close();
	return 0;
}

int GPIO::gpiounexport()
{       
 	std::string unexport_str = "/sys/class/gpio/unexport";
        std::ofstream gpioUnExport(unexport_str.c_str());
        if(!gpioUnExport)
        {       
		std::cout << "GPIO" << this->Num << " Unexport failed!"; 
                return -1;
        }
        
        gpioUnExport << this->Num;
        gpioUnExport.close();
        return 0;

 
}

int GPIO::setdir(std::string dir)
{       
 	std::string pathdir = "/sys/class/gpio/gpio" + this->Num + "/direction";
	std::ofstream setdir(pathdir.c_str());
	
	if(!setdir)
	{
		std::cout << "Error with setting direction for GPIO" << this->Num;
		return -1;
	}

	setdir << dir;
	setdir.close();
 
	return 0;
}

int GPIO::setval(std::string val)
{       	
 	std::string valpath = "/sys/class/gpio/gpio" + this->Num + "/value";
        std::ofstream setval(valpath.c_str());
        
        if(!setval)
        {       
                std::cout << "Error with setting Value for GPIO" << this->Num;
                return -1;
        }
        
        setval << val;
        setval.close();
 
        return 0;

}

int GPIO::getval(std::string& val)
{       	
	std::string valpath = "/sys/class/gpio/gpio" + this->Num + "/value";    
        std::ifstream getval(valpath.c_str()); 
 
       	if(!getval) 
        {                         
                std::cout << "Error with getting Value for GPIO" << this->Num;    
                return -1;
        }
 
        getval >> val;
	if(val != "0")
		val = "1";
	else
		val = "0";

        getval.close();
                          
        return 0;

 
}


std::string GPIO::getNum()
{
	return this->Num;
}

