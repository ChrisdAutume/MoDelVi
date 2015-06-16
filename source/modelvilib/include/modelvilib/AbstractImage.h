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
#include <time.h>
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
            //! State of the image loading
            enum state {
                IMAGE_NOLOADED,
                IMAGE_LOADED,
                IMAGE_UPDATE,
                IMAGE_READY
            };
            
            //! Original image
            IplImage* m_image;
            
            //! Altered image
            IplImage* m_transformImage;
            
            //! m_image on cv::Mar format
            cv::Mat* m_matImage;
            //! m_transformImage on cv::Mar format
            cv::Mat* m_matTransformImage;
            //! State of the image loading
            state m_state;
            //! Region Of Interest used for the FOV cropping
            cv::Rect m_roi;
            
            int m_fov;
            int m_blurr;
            int m_brightness;
            
            //! Timestamp on created time
            time_t m_created;
            
        public:
            ~AbstractImage();
            AbstractImage();
            virtual IplImage* getIplImage();
            virtual cv::Mat* getMatImage();
            virtual cv::Mat* getOriginalMatImage();
            virtual IplImage* getOriginalIplImage();
            
            bool isLoaded();
            
            
            void setFov(int fov);
            void setBlurr(int blurr);
            void setBrightness(int bright);
            
            //! Process the transformation on the image
            void prepareImage();
            /*!
             Used to calcul the coordonate in the original image space in case of using FOV alteration
             @return The coordonate in the original image space.
             @param relativePt Coordonate in the m_transformImage space.
             */
            cv::Point calcFromRelativePoint(cv::Point relativePt);
        };
    }
    
}


#endif	/* ABSTRACTIMAGE_H */

