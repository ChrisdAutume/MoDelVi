/* 
 * File:   BlobMatch.cpp
 * Author: chris
 * 
 * Created on 6 mai 2015, 02:26
 */

#include "modelvilib/BlobMatch.h"
namespace MoDelVi
{

    namespace Analyse
    {

        yarp::os::Bottle BlobMatch::getYarpBottle() {
            yarp::os::Bottle result;
            result.clear();
            
            result.addString("colour");
            result.addString(color);
            result.addDouble(pt.x);
            result.addDouble(pt.y);
            result.addInt(size);
            return result;
        }
        BlobMatch::BlobMatch(cv::Point pt, double size, std::string color) {
            this->pt = pt;
            this->size = size;
            this->color = color;
        }


    }
}
