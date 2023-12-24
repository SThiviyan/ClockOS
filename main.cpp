#include "matrix/include/led-matrix.h"
#include "matrix/include/graphics.h"
#include "UIManager/UIManager.h"

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



static void ActivateInputThread(rotaryButton* pRb)
{
	pRb->automaticPosDetection(true);
}


int main(int argc, char* argv[])
{
	Magick::InitializeMagick(*argv);
	
	RGBMatrix::Options options;
	rgb_matrix::RuntimeOptions runtime_opt;
	options.rows = 32;
	options.cols = 64;
	options.chain_length = 1;
	options.pwm_bits = 11;
	options.brightness = 80;
	options.multiplexing = 0;
	

	RGBMatrix* matrix = RGBMatrix::CreateFromFlags(&argc, &argv, &options);
	rotaryButton* rb = new rotaryButton("26", "21", "20");
	if(matrix == NULL)
		return 0;

	UIManager um(matrix, rb);

	signal(SIGTERM, InterruptHandler);
  	signal(SIGINT, InterruptHandler);
	

	rgb_matrix::Color turqois(0, 255, 255);
	
	bool running = true;
	while(!interrupt_received && running)
	{
		std::thread InputThread(ActivateInputThread, rb);
			um.FirstView(0, turqois);
		InputThread.join();

	}


}	
