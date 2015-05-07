/* 
 * File:   AbstractAnalyser.cpp
 * Author: ced13
 * 
 * Created on 22 April 2015, 12:17
 */

#include <modelvilib/AbstractAnalyser.h>

namespace MoDelVi
{
    namespace Analyse
    {
        AbstractAnalyser::AbstractAnalyser()
        :m_attachedImg(NULL)
        {
        }

        void AbstractAnalyser::setNewImage(Acquisition::AbstractImage* img) {
            m_attachedImg = img;
        }

        AbstractAnalyser::AbstractAnalyser(Acquisition::AbstractImage* img) {
            m_attachedImg = img;
        }

        std::vector<yarp::os::Bottle> AbstractAnalyser::getBottleResult(yarp::os::BufferedPort<yarp::os::Bottle>& outport) {

        }

        void AbstractAnalyser::proceed(Acquisition::AbstractImage* img) {

        }




    }
}
