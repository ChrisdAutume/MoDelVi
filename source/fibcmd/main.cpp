
#include <iostream>
#include <fstream>
#include <string>

//#include <modelvi-version.h>
#include <modelvilib/FileImage.h>
#include <modelvilib/ShapesAnalyser.h>
#include <modelvilib/BlobAnalyser.h>

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
//    std::cout << "Version: " << MODELVI_VERSION << std::endl;  
    
    std::string path = "../../data/sampleIcub/frame";
    
    /*std::cout << "Enter a number between 000 and 377" << std::endl;
    std::string number;
    std::cin >> number;
     * */
    
    std::string fullpath = "";
    fullpath += ".ppm";
    
    MoDelVi::Acquisition::FileImage* file= new MoDelVi::Acquisition::FileImage{"../data/samplePicture/frame147.ppm"};
    //MoDelVi::Acquisition::FileImage* file= new MoDelVi::Acquisition::FileImage{fullpath};
    //MoDelVi::Acquisition::FileImage* file= new MoDelVi::Acquisition::FileImage{"frame000.ppm"};
    //MoDelVi::Analyse::ShapesAnalyser shapes(file);
    MoDelVi::Analyse::BlobAnalyser blob;
   
    
    
    int blurr=3,fov=100, bright=238;
    //cvNamedWindow("Shapes detection");
    cvNamedWindow("Control", 1);
    //cv::createTrackbar("Gray Treshold", "Control", shapes.getGrayTreshold(), 255);
    cv::createTrackbar("Blurr", "Control", &blurr, 255);
    cv::createTrackbar("FOV", "Control", &fov, 100);
    cv::createTrackbar("Brightness 0->200", "Control", &bright, 400);
    int compteur = 100;
    while(true)
    {
        compteur++;
        if(compteur>377) compteur=100;
        delete file;
        std::ostringstream s;
        s << compteur;
        fullpath = path + s.str();
        fullpath += ".ppm";
        file = new MoDelVi::Acquisition::FileImage{fullpath};
        //ODD number is needed for blurr
        while(blurr%2 == 0)
            blurr++;
        if(fov < 1)
            fov = 1;
        
        file->setBlurr(blurr);
        file->setFov(fov);
        file->setBrightness(bright-200);
        file->prepareImage();
        
        //shapes.proceed();
        blob.proceed(file);
        //cvShowImage("Shapes detection", shapes.getResultIpl());
        cv::imshow("Blob detection", *blob.getResultMat());
//while(true)
 //   {
        if (cv::waitKey(50) >= 0)
        {
            std::cout<<"Touch pressed by user. Bye :D"<<std::endl;
            break;
        }
    }

    return 0;
}
