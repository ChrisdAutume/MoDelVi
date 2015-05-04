
#include <iostream>
#include <fstream>
#include <string>

#include <modelvi-version.h>
#include <modelvilib/FileImage.h>
#include <modelvilib/ShapesAnalyser.h>

/**
 * \file main.cpp
 * \brief Sample prog.
 * \author Christian d'Autume <christian.dautume.fr>
 * \version 0.1
 *
 * Sample programme for MoDelVi lib. 
 *
 */


int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "Version: " << MODELVI_VERSION << std::endl;  
    
    MoDelVi::Acquisition::FileImage* file= new MoDelVi::Acquisition::FileImage{"../data/samplePicture/frame147.ppm"};
    //MoDelVi::Acquisition::FileImage* file= new MoDelVi::Acquisition::FileImage{"frame000.ppm"};
    MoDelVi::Analyse::ShapesAnalyser shapes{file};
    
    int blurr=3,fov=100, bright=200;
    cvNamedWindow("Shapes detection");
    cvNamedWindow("Control", 1);
    cv::createTrackbar("Gray Treshold", "Control", shapes.getGrayTreshold(), 255);
    cv::createTrackbar("Blurr", "Control", &blurr, 255);
    cv::createTrackbar("FOV", "Control", &fov, 100);
    cv::createTrackbar("Brightness 0->200", "Control", &bright, 400);

    while(true)
    {
        //ODD number is needed for blurr
        while(blurr%2 == 0)
            blurr++;
        if(fov < 1)
            fov = 1;
        
        file->setBlurr(blurr);
        file->setFov(fov);
        file->setBrightness(bright-200);
        shapes.proceed();
        cvShowImage("Shapes detection", shapes.getResultIpl());
        if (cv::waitKey(30) >= 0)
        {
            std::cout<<"Touch pressed by user. Bye :D"<<std::endl;
            break;
        }
    }

    return 0;
}
