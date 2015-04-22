
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
    std::cout << "Salut c'est moi qui ecrit ce programme :p"<< std::endl;
    std::cout << "Version: " << MODELVI_VERSION << std::endl;
    std::cout << "Oups = " << std::endl;
    std::cout << std::endl;
    MoDelVi::Acquisition::FileImage test("../data/samplePicture/frame000.ppm");
    MoDelVi::Analyse::ShapesAnalyser test2{&test};
    test.reLoadData();
    test2.proceed();
    cvWaitKey(10);
    return 0;
}
