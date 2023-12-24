#include "../matrix/include/led-matrix.h"
#include "../matrix/include/graphics.h"
#include "../rotary/include/rotary.h"
#include "../ImageLib/Imageutils.h"

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>


#include <exception>
#include <Magick++.h>
#include <magick/image.h>
#include <thread>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

class UIManager
{
        public:

        UIManager(RGBMatrix *pm, rotaryButton* pRb){
                this->m = pm;
                this->rb = pRb;

                this->standardOSFont.LoadFont("matrix/fonts/9x18.bdf");
                this->staycurrentview=false;

                InitBackgrounds();
        }

        ~UIManager()
        {
                for(char* file: filenames_backgrounds)
                        delete file;

                delete m;
                delete rb;
        };




        void FirstView(int pbackgroundindex, rgb_matrix::Color color)
        {


                int backgroundindex = pbackgroundindex;
                if(backgroundindex > Backgrounds.size() - 1)
                        backgroundindex = Backgrounds.size() - 1;


                std::thread AnimatedImage(ShowAnimatedImage, Backgrounds[backgroundindex], m);
                        while(true)
                        {
                                DrawText(this->m, this->standardOSFont, 3, 30, color, NULL, "22:22");
                        }

                AnimatedImage.join();

        }


        private:

        void InitBackgrounds()
        {
                filenames_backgrounds.push_back("images/china_cropped_pixelated.gif");
                filenames_backgrounds.push_back("Sunset.gif");

                for(char* file: filenames_backgrounds)
                        Backgrounds.push_back(LoadImageAndScaleImage(file, m->width(), m->height()));
        }


        RGBMatrix* m;
        rotaryButton* rb;

        rgb_matrix::Font standardOSFont;
        bool staycurrentview;
        


        std::vector<char*> filenames_backgrounds;
        std::vector<ImageVector> Backgrounds;
        
};
