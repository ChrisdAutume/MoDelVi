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

        AbstractImage::AbstractImage() : m_fov(new int(100)), m_blurr(new int(3)) {
            
        }

        IplImage* AbstractImage::getIplImage() {
            if(*m_fov < 100 || *m_blurr != 3)
                return m_transformImage;
            return m_image;
        }

        bool AbstractImage::isLoaded() {
            return m_state == IMAGE_LOADED;
        }

        void AbstractImage::prepareImage() {
            
            if(m_state == IMAGE_UPDATE)
            {
                if(*m_fov<100)
                {
                    int height = (m_image->height/100)**m_fov;
                    int width = (m_image->width/100)**m_fov;

                    int x1 = (m_image->width - width)/2;
                    int y1 = (m_image->height - height)/2;

                    cvSetImageROI(m_image, cvRect(x1,y1,width,height));
                    
                    /*
                    if(m_transformImage)
                        cvReleaseImage(&m_transformImage);
                     * */
                }
                m_transformImage = cvCloneImage(m_image);
                
                if(*m_blurr>0)
                    cvSmooth(m_transformImage, m_transformImage, CV_GAUSSIAN,*m_blurr,*m_blurr);
                
                m_state = IMAGE_READY;
                cvResetImageROI(m_image);
                cvShowImage( "Transformed img", m_transformImage );
            }
             
        }

        void AbstractImage::setBlurr(int blurr) {
            if(blurr == *m_blurr)
                return;
            
            *m_blurr = blurr;
            m_state = IMAGE_UPDATE;
            prepareImage();
        }

        void AbstractImage::setFov(int fov) {
            // Need to be in pourcent
            if(fov == *m_fov)
                return;
            
            *m_fov = fov % 100;
            m_state = IMAGE_UPDATE;
            prepareImage();
        }

        AbstractImage::~AbstractImage() {
            cvReleaseImage(&m_image);
        }
    }
}
