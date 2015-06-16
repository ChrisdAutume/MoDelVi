/* 
 * File:   ColorFilter.h
 * Author: chris
 *
 * Created on 9 mai 2015, 13:49
 */

#ifndef COLORFILTER_H
#define	COLORFILTER_H

#include <modelvilib/AbstractImage.h>
#include <iostream>
#include <string>
#include <yarp/sig/all.h>

namespace MoDelVi
{
    namespace Acquisition
    {
        /*!
         @class ColorFilter
         @brief Color filtration for AbstractImage
         */
        class MODELVI_API ColorFilter: public AbstractImage
        {
        public:
            //! Available color filter
            enum m_color {RED_LOW = 0, RED_HIGHT, GREEN, BLUE, YELLOW};
            /*!
             @param image Input image from AbstractImage
             @param color Color to filter. From m_color
             */
            ColorFilter(AbstractImage* image, m_color color );
            ~ColorFilter();
            
            //! Get the name of the color of the filter
            std::string getColor();
            /*!
             Get the BGR color of the border according to the filter in use
             @return List of int in BGR format (color)
             */
            cv::Scalar getBorderColor();
            
            virtual IplImage* getIplImage();
            virtual cv::Mat* getMatImage();


        private:
            //! Filter processing
            void filter();
            
            //! Color used for the filtration
            m_color m_colorFilter;
            
            /*! 
             Range of the color for the filtration. OpenCV HSV color space used.
             To add color, you need to normalize the value from the standard : H = H/2, S = S*2 + 25, V = V*2 + 25
             */
            std::vector< std::vector<int> > m_colorValue; 
            
            //! Input image, not altered by the filter.
            AbstractImage* m_linkedImg;
            
            //! Image in HSV color space
            IplImage* m_hsvImg;
            
        };
    }
}

#endif	/* COLORFILTER_H */

