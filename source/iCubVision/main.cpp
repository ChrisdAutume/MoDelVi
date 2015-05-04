
#include <iostream>
#include <fstream>
#include <string>

#include <modelvi-version.h>
#include <modelvilib/FileImage.h>
#include <modelvilib/ShapesAnalyser.h>

#include <modelvilib/YarpManager.h>

/**
 * \file main.cpp
 * \brief Sample prog.
 * \author Christian d'Autume <christian.dautume.fr>
 * \version 0.1
 *
 * iCub programme. 
 *
 */


int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "Version: " << MODELVI_VERSION << std::endl;  
    MoDelVi::Manager::YarpManager manager;
    manager.createCamera("right");
    manager.createCamera("left");
    return manager.run();
}
