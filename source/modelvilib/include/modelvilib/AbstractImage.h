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
/*!
 * \file AbstractImage.h
 * \brief Abstract class for Image manipulation
 * \author Christian d'Autume
 */

/*! \namespace MoDelVi
 * 
 * Lib namespace.
 */
namespace MoDelVi
{
    /*! \namespace Acquisition
    * 
    * Namespace for Image aquisition procedure.
    */
    namespace Acquisition
    {
        /*! \class Image
        * \brief Abstract class to define basic Image
        *
        *  Abstract class to store image data.
        */
        class MODELVI_API AbstractImage
        {
        protected:
            enum state {
                IMAGE_NOLOADED,
                IMAGE_LOADED,
                IMAGE_UPDATE,
                IMAGE_READY
            };
            IplImage* m_image;
            state m_state = IMAGE_NOLOADED;
            int m_fov;
            int m_blurr;
        public:
            ~AbstractImage(){cvReleaseImage(&m_image);};
            AbstractImage():m_fov(0),m_blurr(0){};
            IplImage* getIplImage()
            {
                return m_image;
            };
            bool isLoaded() { return m_state == IMAGE_LOADED; };
            void setFov(int fov){ m_fov = fov; m_state = IMAGE_UPDATE; };
            void setBlurr(int blurr) { m_blurr = blurr; m_state = IMAGE_UPDATE;}
        };
    }
    
}


#endif	/* ABSTRACTIMAGE_H */

