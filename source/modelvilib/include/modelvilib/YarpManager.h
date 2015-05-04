/* 
 * File:   YarpManager.h
 * Author: chris
 *
 * Created on 4 mai 2015, 02:04
 */

#ifndef YARPMANAGER_H
#define	YARPMANAGER_H
#include "modelvilib/AbstractAnalyser.h"
#include "CamYarp.h"

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <iostream>
#include <vector>
#include <string>

 
namespace MoDelVi
{
    namespace Manager
    {
        class YarpManager : public yarp::os::TypedReaderCallback<yarp::os::Bottle> {
        public:
            YarpManager();
            virtual ~YarpManager();
            int run();
            
            void setAcuity(int acuity);
            void setFov(int fov);
            void setBrightness(int brightness);
            void setTreshold(int threshold);
            
            void createCamera(std::string cameraName);
            
            virtual void onRead(yarp::os::Bottle& b);
        private:
            std::vector<Analyse::AbstractAnalyser*> m_analyser;
            
            //Image parameter
            int m_acuity;
            int m_fov;
            int m_brightness;
            int m_threshold;
            
            //YARP port
            yarp::os::BufferedPort<yarp::os::Bottle> m_parameterPort;
            yarp::os::BufferedPort<yarp::os::Bottle> m_modulePort;
            
            // Camera source
            std::vector<CamYarp*> m_camList;
        };
    }
}

#endif	/* YARPMANAGER_H */

