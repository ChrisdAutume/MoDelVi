/* 
 * File:   CamYarp.h
 * Author: chris
 *
 * Created on 4 mai 2015, 03:19
 */

#ifndef CAMYARP_H
#define	CAMYARP_H

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <iostream>
#include <vector>
#include <string>

#include <modelvilib/YarpImage.h>
#include <modelvilib/AbstractAnalyser.h>
#include <modelvilib/BlobAnalyser.h>
#include <modelvilib/ColorFilter.h>
#include <modelvilib/IParameter.h>
#include <modelvilib/YarpPort.h>
#include <sys/time.h>
#include <time.h>
#include <ctime>

namespace MoDelVi
{
    namespace Manager
    {
        /*!
         @class CamYarp
         @brief Create a independant analyse pipeline who create several YARP port.
         */
        class MODELVI_API CamYarp : public yarp::os::TypedReaderCallback<yarp::sig::ImageOf<yarp::sig::PixelRgb> >, public Yarp::IParameter {
        public:
            /*!
             @param name Name of the pipeline. Determine the name of the YARP namespace
             @param acuity Value of the acuity transformation. See Acquisition::AbstractImage
             @param fov Value of the FOV transformation. See Acquisition::AbstractImage
             @param brightness Value of the brightness alteration. See Acquisition::AbstractImage
             @param threshold Not in use at the moment
             */
            CamYarp(std::string name, int* acuity, int* fov, int* brightness, int* threshold);
            virtual ~CamYarp();
            
            /*!
             Callback for YARP port. Call when a image is buffered by the YARP port.
             @param b Image from the YARP network. RGB format.
             */
            virtual void onRead(yarp::sig::ImageOf<yarp::sig::PixelRgb>& b);
            
            /*!
             Callback for the YarpPort. Call when a bottle is receveid by the port.
             @param parameterName Name of the parameter
             @param b YARP bottle from the port
             */
            virtual void onBottle(std::string parameterName, yarp::os::Bottle &b);
            
            //! @return List of the analyser
            std::vector<Analyse::AbstractAnalyser*>* getAnalyserPtr();

        private:
            //! Name of the pipeline and YARP namespace of the object
            std::string m_name;
            
            int *m_acuity;
            int *m_fov;
            int *m_brightness;
            int *m_threshold;
            
            /*!
             Send image througt the out port of the pipeline. Usually used to return original image with match result.
             @param img Image to output. cv::Mat format
             */
            void outputMatImage(cv::Mat &img);
            /*!
            Send image througt the out port of the pipeline. Usually used to return original image with match result.
            @param img Image to output. IplImage format
            */
            void outputIplImage(IplImage &img);
            
            //! Timestamp of the last image
            std::clock_t m_lastImg;
            
            //! Input YARP port object. Used to get image from the network
            yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > m_inPort;
            //! Output YARP port object. Used to inject the processed image in the network.
            yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelBgr> > m_outPort;
            
            //! Input YARP port object. Used to send analyser result to the network.
            Yarp::YarpPort* m_dataPort;
            //! List of the loaded analyser.
            std::vector<Analyse::AbstractAnalyser*> m_analyser;

        };
    }
}

#endif	/* CAMYARP_H */

