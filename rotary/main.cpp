include <iostream>
#include "../rotary/include/rotary.h"
#include <unistd.h>
#include <thread>




void startUI(rotaryButton* r)
{

	r->automaticPosDetection(true);

}

int main()
{
	rotaryButton* r = new rotaryButton("0", "5", "6");	


	std::thread t1(
	startUI, r);

	while(true)
	{
		if(r->getPosition() > 20)
        	{       
                	std::cout << "Switch Menu" << std::endl;
        	}

		usleep(1000);
	}
	

        t1.join();


	return 0;
}
