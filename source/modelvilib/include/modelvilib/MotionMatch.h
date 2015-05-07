/* 
 * File:   MotionMatch.h
 * Author: chris
 *
 * Created on 7 mai 2015, 20:35
 */

#ifndef MOTIONMATCH_H
#define	MOTIONMATCH_H

#include <modelvilib/modelvi_api.h>
#include <opencv2/opencv.hpp>

#include <yarp/os/all.h>

namespace MoDelVi
{

    namespace Analyse
    {

        class MotionMatch
        {
        public:
            cv::Point oldPt;
            cv::Point newPt;
            double speed;
            
            MotionMatch(cv::Point startPt, cv::Point endPt, double motionSpeed);
            yarp::os::Bottle getYarpBottle(yarp::os::BufferedPort<yarp::os::Bottle>& outport);
        };
    }
    
}

#endif	/* MOTIONMATCH_H */

