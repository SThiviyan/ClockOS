#include "matrix/include/led-matrix.h"
#include "rotary/include/rotary.h"
#include "ImageLib/Imageutils.cpp"

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


static void UIManager(RGBMatrix* pm, rotaryButton* pRb)
{
	const char* filename = "images/burger.gif"; 
	const char* filename2 = "images/Icecream.gif";
	const char* filename3 = "images/Sunset.gif";


	ImageVector images = LoadImageAndScaleImage(filename, pm->width() , pm->height());
 	ImageVector images2 = LoadImageAndScaleImage(filename2, pm->width(), pm->height());
	ImageVector images3 = LoadImageAndScaleImage(filename3, pm->width(), pm->height());


	std::thread AnimatedImageThread(
	ShowAnimatedImage, images, pm);
		while(true)
		{
			pm->SetPixel(50, 30, pRb->getPosition() * 5.6, pRb->getPosition() * 1.07, pRb->getPosition() * 2.4);		
		}

	
	AnimatedImageThread.join();
	
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

	signal(SIGTERM, InterruptHandler);
  	signal(SIGINT, InterruptHandler);
	

	
	bool running = true;
	while(!interrupt_received && running)
	{
		std::thread InputThread(ActivateInputThread, rb);
			UIManager(matrix, rb);
		InputThread.join();

	}


}	
