/* 
 * File:   AbstractAnalyser.h
 * Author: ced13
 *
 * Created on 22 April 2015, 12:17
 */

#ifndef ABSTRACTANALYSER_H
#define	ABSTRACTANALYSER_H

#include <modelvilib/modelvi_api.h>
#include <modelvilib/AbstractImage.h>
#include <opencv2/opencv.hpp>
#include <yarp/os/all.h>
#include <iostream>
/*! \namespace MoDelVi
 * 
 * Lib namespace.
 */
namespace MoDelVi
{
    /*! \namespace Acquisition
    * 
    * Namespace for Image aquisition procedure.
    */
    namespace Analyse
    {
        /*! \class AbstractAnalyser
        * \brief Abstract class to define basic Analyser
        *
        *  Abstract class to store image data.
        */
        class MODELVI_API AbstractAnalyser
        {
        protected:
            Acquisition::AbstractImage* m_attachedImg;
        public:
            AbstractAnalyser(Acquisition::AbstractImage* img);
            AbstractAnalyser();
            
            virtual void setNewImage(Acquisition::AbstractImage* img);
            virtual void proceed() =0;
            virtual void proceed(Acquisition::AbstractImage* img);
            virtual std::vector<yarp::os::Bottle> getBottleResult(yarp::os::BufferedPort<yarp::os::Bottle>& outport);
        };
    }
    
}

#endif	/* ABSTRACTANALYSER_H */

