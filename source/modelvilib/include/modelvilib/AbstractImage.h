/* 
 * File:   AbstractImage.h
 * Author: ced13
 *
 * Created on 15 April 2015, 15:25
 */

#ifndef ABSTRACTIMAGE_H
#define	ABSTRACTIMAGE_H

#include <opencv2/opencv.hpp>
namespace MoDelVi
{
    namespace Acquisition
    {
        class Image
        {
            IplImage* m_image;
        public:
            Image();
            IplImage* getIplImage() = 0
            {
                return m_image;
            };
        };
    }
    
}


#endif	/* ABSTRACTIMAGE_H */

