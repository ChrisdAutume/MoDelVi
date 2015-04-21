/* 
 * File:   AbstractImage.h
 * Author: ced13
 *
 * Created on 15 April 2015, 15:25
 */

#ifndef ABSTRACTIMAGE_H
#define	ABSTRACTIMAGE_H

#include <modelvilib/modelvi_api.h>
#include <opencv2/opencv.hpp>

namespace MoDelVi
{
    namespace Acquisition
    {
        class MODELVI_API Image
        {
        protected:
            enum state {
                IMAGE_NOLOADED,
                IMAGE_LOADED
            };
            IplImage* m_image;
            state m_state = IMAGE_NOLOADED;
        public:
            
            IplImage* getIplImage()
            {
                return m_image;
            };
            bool isLoaded() { return m_state == IMAGE_LOADED; };
        };
    }
    
}


#endif	/* ABSTRACTIMAGE_H */

