/* 
 * File:   BlobMatch.h
 * Author: chris
 *
 * Created on 6 mai 2015, 02:26
 */

#ifndef BLOBMATCH_H
#define	BLOBMATCH_H

#include <modelvilib/modelvi_api.h>
#include <opencv2/opencv.hpp>
#include <modelvilib/YarpPort.h>
#include <yarp/os/all.h>
namespace MoDelVi
{

    namespace Analyse
    {
        /*!
         @class BlobMatch
         @brief Object to store BlobAnalyser matches' details.
         */
        class MODELVI_API BlobMatch
        {
        public:
            //! Center point of the match
            cv::Point pt;
            //! Size of the match
            double size;
            //! Color of the detected color
            std::string color;
            
            BlobMatch(cv::Point pt, double size, std::string color);
            /*!
             Prepare the output througt the YARP network.
             @param output YarpPort objet of the output port in the network.
             @return BlobMatch data in a YARP bottle.
             */
            yarp::os::Bottle getYarpBottle(Yarp::YarpPort& outport);
        };
    }
    
}

#endif	/* BLOBMATCH_H */

