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
            IplImage* m_transformImage;
            state m_state = IMAGE_NOLOADED;
            
            int m_fov;
            int m_blurr;
            int m_brightness;
            
            cv::Point m_RoiPt;
            
            void prepareImage();
        public:
            ~AbstractImage();
            AbstractImage();
            IplImage* getIplImage();
            bool isLoaded();
            
            
            void setFov(int fov);
            void setBlurr(int blurr);
            void setBrightness(int bright);
            
            cv::Point calcFromRelativePoint(cv::Point relativePt);
        };
    }
    
}


#endif	/* ABSTRACTIMAGE_H */

