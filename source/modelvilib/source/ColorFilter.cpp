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
            
            m_colorFilter = color;
            m_linkedImg = image;
            
            m_image = cvCreateImage(cvGetSize(m_linkedImg->getIplImage()), 8, 3);
            cvCopy(m_linkedImg->getIplImage(), m_image);
            m_matImage = m_linkedImg->getMatImage();
            filter();
        }

        void ColorFilter::filter() {
            std::vector<int> hLevel;
            std::vector<int> lLevel;
            
            m_hsvImg = cvCreateImage(cvGetSize(m_image), 8, 3);
            cvCvtColor(m_image, m_hsvImg, CV_BGR2HSV);
            m_transformImage = cvCreateImage(cvGetSize(m_image), 8, 1);
            switch(m_colorFilter)
            {
                case RED_LOW:
                    lLevel.push_back(0); // Half of HUE
                    lLevel.push_back(120); // x2 + 25 of S
                    lLevel.push_back(110); // x2 + 25 of V
                    
                    hLevel.push_back(7);
                    hLevel.push_back(225);
                    hLevel.push_back(225);
                    break;
                case GREEN:
                    lLevel.push_back(73);
                    lLevel.push_back(225);
                    lLevel.push_back(225);
                    
                    hLevel.push_back(44);
                    hLevel.push_back(75);
                    hLevel.push_back(90);
                    break;
                default:
                    hLevel.push_back(0);
                    hLevel.push_back(0);
                    hLevel.push_back(0);
                    
                    lLevel.push_back(0);
                    lLevel.push_back(0);
                    lLevel.push_back(0);
            };
            cvInRangeS(m_hsvImg, cvScalar(lLevel.at(0), lLevel.at(1), lLevel.at(2)), cvScalar(hLevel.at(0), hLevel.at(1), hLevel.at(2)), m_transformImage);
            
            cvErode(m_transformImage,m_transformImage,NULL,3);
            cvDilate(m_transformImage,m_transformImage,NULL,6);

            //Conv to Matrice
            m_matTransformImage = new cv::Mat(m_transformImage);
        }
        std::string ColorFilter::getColor()
        {
            std::string result;
            switch (m_colorFilter) {
                case RED_HIGHT:
                case RED_LOW:
                    result = "red";
                    break;
                case BLUE:
                    result = "blue";
                    break;
                case YELLOW:
                    result = "yellow";
                    break;
                case GREEN:
                    result = "green";
                    break;
                    
                default:
                    result = "any";
            }
            return result;
        }
        
        cv::Scalar ColorFilter::getBorderColor()
        {
            switch (m_colorFilter) {
                case RED_HIGHT:
                case RED_LOW:
                    return cv::Scalar(0,0,255); break;
                case BLUE:
                    return cv::Scalar(255,0,0); break;
                case YELLOW:
                    return cv::Scalar(0,255,255); break;
                case GREEN:
                    return cv::Scalar(0,255,0); break;
                    
                default:
                    return cv::Scalar(0,0,0);
            }
        }
        ColorFilter::~ColorFilter() {
            cvReleaseImage(&m_hsvImg);
            cvReleaseImage(&m_transformImage);
        }

        IplImage* ColorFilter::getIplImage() {
            return m_transformImage;
        }
        cv::Mat* ColorFilter::getMatImage() {
            return m_matTransformImage;        
        }



    }
}