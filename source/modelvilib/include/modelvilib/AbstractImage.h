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

