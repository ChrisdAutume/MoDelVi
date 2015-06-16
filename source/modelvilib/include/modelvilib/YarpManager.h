/* 
 * File:   YarpManager.h
 * Author: chris
 *
 * Created on 4 mai 2015, 02:04
 */

#ifndef YARPMANAGER_H
#define	YARPMANAGER_H
#include <modelvilib/AbstractAnalyser.h>
#include <modelvilib/YarpPort.h>
#include <modelvilib/IParameter.h>
#include <modelvilib/CamYarp.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <iostream>
#include <vector>
#include <string>


 
namespace MoDelVi
{
    namespace Manager
    {
        /*!
         @class YarpManager
         @brief YARP module implementation, autonomous program. Just lauch run() function. Create channel. Generale namespace can be set with YarpPort instance.
         */
        class MODELVI_API YarpManager : public Yarp::IParameter {
        public:
            YarpManager();
            ~YarpManager();
            
            //! Lauch the main process.
            int run();
            
            void setAcuity(int acuity);
            void setFov(int fov);
            void setBrightness(int brightness);
            void setTreshold(int threshold);
            
            //! Create an analyse pipeline, also create a YARP namespace
            void createCamera(std::string cameraName);

            virtual void onBottle(std::string parameterName, yarp::os::Bottle &b);
        private:
            //! List of loaded anayser
            std::vector<Analyse::AbstractAnalyser*> m_analyser;
            
            //Image parameter
            int m_acuity;
            int m_brightness;
            int m_fov;
            int m_threshold;
            
            //! YARP parameter port
            Yarp::YarpPort* m_parameterPort;
            //! YARP module parameter port
            Yarp::YarpPort* m_modulePort;
            
            //! List of the pipeline instance
            std::vector<CamYarp*> m_camList;
        };
    }
}

#endif	/* YARPMANAGER_H */

