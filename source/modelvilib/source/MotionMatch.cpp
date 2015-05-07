/* 
 * File:   MotionMatch.cpp
 * Author: chris
 * 
 * Created on 7 mai 2015, 20:35
 */

#include "modelvilib/MotionMatch.h"
namespace MoDelVi
{

    namespace Analyse
    {

        yarp::os::Bottle MotionMatch::getYarpBottle(yarp::os::BufferedPort<yarp::os::Bottle>& outport) {
            yarp::os::Bottle& result = outport.prepare();
            result.clear();
            
            result.addString("motion");
            result.addDouble(speed);
            result.addDouble(oldPt.x);
            result.addDouble(oldPt.y);
            result.addDouble(newPt.x);
            result.addDouble(newPt.y);
            outport.writeStrict();
            return result;
        }

        MotionMatch::MotionMatch(cv::Point startPt, cv::Point endPt, double motionSpeed) {
            newPt = endPt;
            oldPt = startPt;
            speed = motionSpeed;
        }
        


    }
}

