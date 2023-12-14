#include "matrix/include/led-matrix.h"
#include "rotary/include/rotary.h"


#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>


#include <exception>
#include <Magick++.h>
#include <magick/image.h>
#include <thread>


using rgb_matrix::Canvas;
using rgb_matrix::RGBMatrix;
using rgb_matrix::FrameCanvas;


volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}




static void ActivateInputThread(rotary* pRb)
{
	pRb->automaticPosDetection(true);
}


int main(int argc, char* argv[])
{
	std::cout << "Test";
	
	RGBMatrix::Options options;
	rgb_matrix::RuntimeOptions runtime_opt;
	options.rows = 32;
	options.cols = 64;
	options.chain_length = 1;
	options.pwm_bits = 11;
	options.brightness = 100;
	options.multiplexing = 1;
	

	RGBMatrix* matrix = RGBMatrix::CreateFromOptions(options, runtime_opt);
	rotary* rb = rotaryButton("26", "20", "21");
	if(matrix == NULL)
		return usage(argv[0]);

	rgb_matrix::FrameCanvas* canvas = matrix->CreateFrameCanvas();
	signal(SIGTERM, InterruptHandler);
  	signal(SIGINT, InterruptHandler);
	

	
	bool running = true;
	while(!interrupt_received && running)
	{
		std::thread InputThread(ActivateInputThread, rb);
	
			while(running)
			{
				canvas->Clear();
	
				rgb_matrix::Color blue = rgb_matrix::Color(255, 0, 0); 
				canvas->SetPixels(10, 10, 20, 20, blue);			
				int pos = rb->getPosition();

				std::cout << pos << std::endl;
			}
		InputThread.join();

	}


}	
