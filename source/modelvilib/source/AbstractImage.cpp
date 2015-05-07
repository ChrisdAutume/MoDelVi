/* 
 * File:   AbstractImage.cpp
 * Author: ced13
 * 
 * Created on 22 April 2015, 12:17
 */

#include <modelvilib/AbstractImage.h>

namespace MoDelVi
{
    namespace Acquisition
    {

        AbstractImage::AbstractImage() : m_fov(100), m_blurr(3), m_brightness(0) {
            m_state = IMAGE_NOLOADED;
            m_transformImage = NULL;
            m_matTransformImage = NULL;
            m_roi.x = 0; m_roi.y = 0;
            m_matImage = NULL;
        }

        IplImage* AbstractImage::getIplImage() {
            if(m_fov < 100 ||m_blurr != 3 || m_brightness != 0)
                return m_transformImage;
            return m_image;
        }

        cv::Mat* AbstractImage::getMatImage() {
            if(m_matTransformImage)
                return m_matTransformImage;
            return m_matImage;
        }

        bool AbstractImage::isLoaded() {
            return m_state == IMAGE_LOADED;
        }

        void AbstractImage::prepareImage() {
            
            if(m_state == IMAGE_UPDATE)
            {
                if(m_fov<100)
                {
                    
                    m_roi.height = (m_image->height/100.0)*m_fov;
                    m_roi.width = (m_image->width/100.0)*m_fov;
 
                    m_roi.x = (m_image->width - m_roi.width)/2.0;
                    m_roi.y = (m_image->height - m_roi.height)/2.0;
                    
                    cvSetImageROI(m_image, cvRect(m_roi.x,m_roi.y,m_roi.width,m_roi.height)); 
                    
                }
                if(m_transformImage!= NULL)
                        cvReleaseImage(&m_transformImage);
                
                m_transformImage = cvCloneImage(m_image);
                
                if(m_brightness != 0)
                    m_transformImage += cv::Scalar(m_brightness,m_brightness,m_brightness);
                
                if(m_blurr>0)
                    cvSmooth(m_transformImage, m_transformImage, CV_GAUSSIAN,m_blurr,m_blurr);
       
                m_state = IMAGE_LOADED;
                cvResetImageROI(m_image);
                
                if(m_matTransformImage)
                    delete m_matTransformImage;
                m_matTransformImage = new cv::Mat(m_transformImage);
                
            }
             
        }

        void AbstractImage::setBlurr(int blurr) {
            if(blurr == m_blurr)
                return;
            
            m_blurr = blurr;
            m_state = IMAGE_UPDATE;
        }

        void AbstractImage::setFov(int fov) {
            // Need to be in pourcent
            if(fov == m_fov)
                return;
            
            m_fov = fov % 101;
            m_state = IMAGE_UPDATE;
        }

        void AbstractImage::setBrightness(int bright) {
            if(bright == m_brightness)
                return;
            
            m_brightness = bright;
            m_state = IMAGE_UPDATE;     
        }


        AbstractImage::~AbstractImage() {
            cvReleaseImage(&m_image);
            cvReleaseImage(&m_transformImage);
            m_matImage->release(); 
            delete m_matImage;
        }
        
        cv::Point AbstractImage::calcFromRelativePoint(cv::Point relativePt) {
            cv::Point result;
            result.x = relativePt.x+m_roi.x;
            result.y = relativePt.y+m_roi.y;
            
            return result;
        }

    }
}
