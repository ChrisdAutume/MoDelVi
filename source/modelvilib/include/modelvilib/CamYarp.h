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

namespace MoDelVi
{
    namespace Manager
    {
        class MODELVI_API CamYarp : public yarp::os::TypedReaderCallback<yarp::sig::ImageOf<yarp::sig::PixelRgb> > {
        public:
            CamYarp(std::string name, int* acuity, int* fov, int* brightness, int* threshold);
            virtual ~CamYarp();
            virtual void onRead(yarp::sig::ImageOf<yarp::sig::PixelRgb>& b);
            
            std::vector<Analyse::AbstractAnalyser*>* getAnalyserPtr();

        private:
            std::string m_name;
            
            int *m_acuity;
            int *m_fov;
            int *m_brightness;
            int *m_threshold;
            
            void outputMatImage(cv::Mat &img);
            void outputIplImage(IplImage &img);
            
            yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > m_inPort;
            yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelBgr> > m_outPort;
            yarp::os::BufferedPort<yarp::os::Bottle> m_dataPort;
            
            std::vector<Analyse::AbstractAnalyser*> m_analyser;

        };
    }
}

#endif	/* CAMYARP_H */

