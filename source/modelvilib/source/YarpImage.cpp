/* 
 * File:   YarpImage.cpp
 * Author: chris
 * 
 * Created on 6 mai 2015, 00:50
 */

#include <modelvilib/YarpImage.h>

namespace MoDelVi
{
    namespace Acquisition
    {

        YarpImage::YarpImage(yarp::sig::ImageOf<yarp::sig::PixelRgb>* image) {
            toOpenCV(image);
        }

        void YarpImage::toOpenCV(yarp::sig::ImageOf<yarp::sig::PixelRgb>* image) {
            IplImage* tmp_image = (IplImage*) image->getIplImage();
            m_image = cvCreateImage( cvSize(tmp_image->width,  tmp_image->height),tmp_image->depth, 3 );
            cvCvtColor(tmp_image, m_image, CV_RGB2BGR);
            m_image->origin = 0;
            
            m_state = IMAGE_LOADED;
        }


    }
}