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

#include <yarp/os/all.h>
namespace MoDelVi
{

    namespace Analyse
    {

        class MODELVI_API BlobMatch
        {
        public:
            cv::Point pt;
            double size;
            std::string color;
            
            BlobMatch(cv::Point pt, double size, std::string color);
            yarp::os::Bottle getYarpBottle(yarp::os::BufferedPort<yarp::os::Bottle>& outport);
        };
    }
    
}

#endif	/* BLOBMATCH_H */

