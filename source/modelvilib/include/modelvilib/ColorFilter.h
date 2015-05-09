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
        class MODELVI_API ColorFilter: public AbstractImage
        {
        public:
            enum m_color {RED_LOW, RED_HIGHT, GREEN, BLUE, YELLOW};
            ColorFilter(AbstractImage* image, m_color color );
            ~ColorFilter();

            virtual IplImage* getIplImage();
            virtual cv::Mat* getMatImage();


        private:
            void filter();
            m_color m_colorFilter;
            std::vector< std::vector<int> > m_colorValue; 
            
            AbstractImage* m_linkedImg;
            IplImage* m_hsvImg;
            
        };
    }
}

#endif	/* COLORFILTER_H */

