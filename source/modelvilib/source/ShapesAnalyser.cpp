/* 
 * File:   ShapesAnalyser.cpp
 * Author: ced13
 * 
 * Created on 22 April 2015, 12:27
 */

#include <modelvilib/ShapesAnalyser.h>

namespace MoDelVi
{
    namespace Analyse
    {

        ShapesAnalyser::ShapesAnalyser(): AbstractAnalyser() {
        }
        ShapesAnalyser::ShapesAnalyser(Acquisition::AbstractImage* img)
        :AbstractAnalyser(img)
        {
            std::cout<<"Shapes Loaded"<<std::endl;
            if(m_attachedImg->isLoaded())
                std::cout<<"Img loaded in class"<<std::endl;
        }

        void ShapesAnalyser::proceed() {
            filter();
            cvNamedWindow("Test");   
            //cvShowImage("Test", m_greyScale);
        }

        void ShapesAnalyser::filter() {
            cvSmooth(m_attachedImg, m_attachedImg, CV_GAUSSIAN,3,3); 
            m_greyScale = cvCreateImage(cvGetSize(m_attachedImg), 8, 1); 
            cvCvtColor(m_attachedImg,m_greyScale,CV_BGR2GRAY);
            cvThreshold(m_greyScale,m_greyScale,100,255,CV_THRESH_BINARY_INV);
        }

        
        


    }
}
