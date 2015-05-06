/* 
 * File:   YarpImage.h
 * Author: chris
 *
 * Created on 6 mai 2015, 00:50
 */

#ifndef YARPIMAGE_H
#define	YARPIMAGE_H

#include <modelvilib/AbstractImage.h>
#include <iostream>
#include <string>
#include <yarp/sig/all.h>

namespace MoDelVi
{
    namespace Acquisition
    {
        class MODELVI_API YarpImage: public AbstractImage
        {
        public:
            YarpImage(yarp::sig::ImageOf<yarp::sig::PixelRgb>* image);
        private:
            void toOpenCV(yarp::sig::ImageOf<yarp::sig::PixelRgb>* image);
        };
    }
}

#endif	/* YARPIMAGE_H */

