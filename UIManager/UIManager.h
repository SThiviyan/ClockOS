#pragma once

#include "../matrix/include/led-matrix.h"
#include "../rotary/include/rotary.h"
#include "../ImageLib/Imageutils.h"
#include "../UtilLib/timeutils.h"
#include "../matrix/include/graphics.h"

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include <exception>
#include <Magick++.h>
#include <magick/image.h>
#include <thread>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

class UIManager
{
        public:

        UIManager(RGBMatrix *pm, rotaryButton* pRb);

        ~UIManager();
	
	void runUI();

        int FirstView(int pbackgroundindex, rgb_matrix::Color color, int* running);


	private:

        void InitBackgrounds();

        RGBMatrix* m;
        rotaryButton* rb;

        rgb_matrix::Font standardOSFont;
        bool staycurrentview;
        


        std::vector<char*> filenames_backgrounds;
        std::vector<ImageVector> Backgrounds;
        
};
