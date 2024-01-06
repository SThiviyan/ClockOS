#include "UIManager.h"
#include "../UtilLib/timeutils.h"



UIManager::UIManager(RGBMatrix* pm, rotaryButton* pRb)
{
	this->m = pm;
        this->rb = pRb;

        this->standardOSFont.LoadFont("matrix/fonts/6x10.bdf");
        this->staycurrentview=false;

        InitBackgrounds();
}




UIManager::~UIManager()
{
	for(char* file: this->filenames_backgrounds)
		delete file;


        delete m;
        delete rb;
}


void Test()
{
	std::cout << "Button Pressed";

}

int UIManager::FirstView(int pbackgroundindex, rgb_matrix::Color color, int* running)
{


        long unsigned int backgroundindex = pbackgroundindex;
        if(backgroundindex > Backgrounds.size() - 1)
		backgroundindex = Backgrounds.size() - 1;



	this->rb->SetPressCallback(&Test);

        std::thread AnimatedImage(ShowAnimatedImage, Backgrounds[backgroundindex], m, running);
                while(true)
		{

			
			DrawText(this->m, this->standardOSFont, 3, 30, color, NULL, getcurrentDateTime("%H:%M:%S").c_str());      
		}

        AnimatedImage.join();
	
	return 0;
}


void UIManager::InitBackgrounds()
{
       	this->filenames_backgrounds.push_back("images/china_cropped_pixelated.gif");
        this->filenames_backgrounds.push_back("Sunset.gif");

        for(char* file: this->filenames_backgrounds)
                Backgrounds.push_back(LoadImageAndScaleImage(file, this->m->width(), this->m->height()));
}
