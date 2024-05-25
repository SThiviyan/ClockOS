#include <iostream>
#include "include/rotary.h"
#include <unistd.h>
#include <thread>




void startUI(rotaryButton* r)
{

	r->automaticPosDetection(true);

}


void callback()
{
	std::cout << "Button pressed" << std::endl;
}


void callback2()
{
	std::cout << "Callback switched" << std::endl;
}


int main()
{
	rotaryButton* r = new rotaryButton("26", "16", "6");	
	r->SetPressCallback(callback);


	std::thread t1(
	startUI, r);

	while(true)
	{
		std::cout << r->getPosition() << std::endl;
		
		//usleep();
	}
	

        t1.join();


	return 0;
}
