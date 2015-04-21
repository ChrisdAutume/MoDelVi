
#include <iostream>
#include <fstream>
#include <string>

#include <modelvi-version.h>
#include <modelvilib/FileImage.h>

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "Salut c'est moi qui ecrit ce programme :p"<< std::endl;
    std::cout << "Version: " << MODELVI_VERSION << std::endl;
    std::cout << "Oups = " << std::endl;
    std::cout << std::endl;
    MoDelVi::Acquisition::FileImage test("/aber/ced13/Desktop/MoDelVi/data/samplePicture/frame000.ppm");
    test.reLoadData();
    return 0;
}
