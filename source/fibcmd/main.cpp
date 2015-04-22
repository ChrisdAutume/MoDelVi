
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
    
    MoDelVi::Acquisition::FileImage test{"../data/samplePicture/crop.ppm"};
    MoDelVi::Analyse::ShapesAnalyser test2{&test};
    
    while(true)
    {
        test2.proceed();
        s
        cvNamedWindow("Resultat");
        cvShowImage("Resultat", test2.getResultIpl());
        if (cv::waitKey(30) >= 0)
        {
            std::cout<<"Touch pressed by user. Bye :D"<<std::endl;
            break;
        }
    }
    return 0;
}
