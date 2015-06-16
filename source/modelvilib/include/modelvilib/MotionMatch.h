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
#include <modelvilib/YarpPort.h>

#include <yarp/os/all.h>

namespace MoDelVi
{

    namespace Analyse
    {
        /*! 
         @class MotionMatch
         @brief Object to store motion details.
         */
        class MODELVI_API MotionMatch
        {
        public:
            //! Position of the object before the motion.
            cv::Point oldPt;
            //! New position of the object
            cv::Point newPt;
            //! Speed of the motion
            double speed;
            
            /*!
             @param startPt Old position of the object before the motion
             @param endPt Position of the object after the motion
             @param motionSpeed Speed of the motion in px/s
             */
            MotionMatch(cv::Point startPt, cv::Point endPt, double motionSpeed);
            yarp::os::Bottle getYarpBottle(Yarp::YarpPort& outport);
        };
    }
    
}

#endif	/* MOTIONMATCH_H */

