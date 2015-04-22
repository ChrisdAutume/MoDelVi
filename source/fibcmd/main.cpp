
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
    
    MoDelVi::Acquisition::FileImage file{"../data/samplePicture/simple.png"};
    MoDelVi::Analyse::ShapesAnalyser shapes{&file};
    
    cvNamedWindow("Shapes detection");
    while(true)
    {
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
