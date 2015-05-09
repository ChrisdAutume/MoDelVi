/* 
 * File:   ColorFilter.cpp
 * Author: chris
 * 
 * Created on 9 mai 2015, 13:49
 */

#include <modelvilib/ColorFilter.h>
namespace MoDelVi
{
    namespace Acquisition
    {

        ColorFilter::ColorFilter(AbstractImage* image, m_color color) {
            
            // Define color
            // RED
            //m_colorValue.push_back((int)RED_LOW, std::vector<int>());
            
            m_colorFilter = color;
            m_linkedImg = image;
            
            m_image = cvCreateImage(cvGetSize(m_linkedImg->getIplImage()), 8, 3);
            cvCopy(m_linkedImg->getIplImage(), m_image);
            m_matImage = m_linkedImg->getMatImage();
            filter();
        }

        void ColorFilter::filter() {
            std::vector<int> hightLevel;
            std::vector<int> lowLevel;
            
            m_hsvImg = cvCreateImage(cvGetSize(m_image), 8, 3);
            cvCvtColor(m_image, m_hsvImg, CV_BGR2HSV);
            m_transformImage = cvCreateImage(cvGetSize(m_image), 8, 1);
            
            switch(m_colorFilter)
            {
                case RED_LOW:
                    hightLevel.push_back(0); // Half of HUE
                    hightLevel.push_back(120); // x2 + 25 of S
                    hightLevel.push_back(110); // x2 + 25 of V
                    
                    lowLevel.push_back(7);
                    lowLevel.push_back(225);
                    lowLevel.push_back(225);
                    break;
                case GREEN:
                    lowLevel.push_back(73);
                    lowLevel.push_back(225);
                    lowLevel.push_back(225);
                    
                    hightLevel.push_back(44);
                    hightLevel.push_back(75);
                    hightLevel.push_back(90);
                    break;
                default:
                    hightLevel.push_back(0);
                    hightLevel.push_back(0);
                    hightLevel.push_back(0);
                    
                    lowLevel.push_back(0);
                    lowLevel.push_back(0);
                    lowLevel.push_back(0);
            }
            cvInRangeS(m_hsvImg, cvScalar(hightLevel.at(0), hightLevel.at(1), hightLevel.at(2)), cvScalar(lowLevel.at(0), lowLevel.at(1), lowLevel.at(2)), m_transformImage);
            
            cvErode(m_transformImage,m_transformImage,NULL,3);
            cvDilate(m_transformImage,m_transformImage,NULL,3);
 
            //cv::bitwise_not(m_hsvImg,m_hsvImg);
            //Conv to Matrice
            m_matTransformImage = new cv::Mat(m_transformImage);
        }

        ColorFilter::~ColorFilter() {
            cvReleaseImage(&m_hsvImg);
        }

        IplImage* ColorFilter::getIplImage() {
            return m_transformImage;
        }
        cv::Mat* ColorFilter::getMatImage() {
            return m_matTransformImage;        
        }



    }
}