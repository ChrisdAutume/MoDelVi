/* 
 * File:   YarpManager.cpp
 * Author: chris
 * 
 * Created on 4 mai 2015, 02:04
 */

#include "modelvilib/YarpManager.h"

 
namespace MoDelVi
{
    namespace Manager
    {
        YarpManager::YarpManager():
        m_acuity(0),
        m_brightness(0),
        m_fov(0),
        m_threshold(0)
        {
            std::cout<<"## YarpManager Initialisation ##"<<std::endl;
            std::cout<<"- Setting default parameters value"<<std::endl;
            setAcuity(3);
            setFov(100);
            setBrightness(50);
            setTreshold(150);
            
            std::cout<<"- Setting up YARP network"<<std::endl;
            yarp::os::Network::init();
            std::cout<<"- Opening YARP port"<<std::endl;
            std::cout<<"    * /target/module"<<std::endl;
            m_modulePort = new Yarp::YarpPort("module");
            m_modulePort->attachListener(this); //No need to listen
            
            std::cout<<"    * /target/parameter"<<std::endl;
            m_parameterPort= new Yarp::YarpPort("parameter");
            m_parameterPort->attachListener(this);
        }
        void YarpManager::onBottle(std::string parameterName, yarp::os::Bottle &b)
        {
            if(parameterName == "parameter")
            {
                std::string name = b.get(0).asString().c_str();
                int value = b.get(1).asInt();
                
                if(name == "acuity") setAcuity(value);
                else if(name == "fov") setFov(value);
                else if(name == "brightness") setBrightness(value);
                else if(name == "threshold") setTreshold(value);
            }
            
        }

        YarpManager::~YarpManager() {
            delete m_modulePort;
            delete m_parameterPort;
            yarp::os::Network::fini();
        }

        void YarpManager::createCamera(std::string cameraName) {
            CamYarp* cam = new CamYarp(cameraName,&m_acuity,&m_fov,&m_brightness,&m_threshold);
            m_camList.push_back(cam);
            m_modulePort->attachListener(cam);
        }

        int YarpManager::run() {
            std::cout<<"## YarpManager Running ##"<<std::endl;
            bool running = true;
            while(running)
            {
                yarp::os::Time::delay(1);
            }
            return 0;
        }
        void YarpManager::setAcuity(int acuity) {
            while(acuity%2==0)
                acuity++;
            
            std::cout<<"** Acuity updated. Old: "<<m_acuity<<" New: "<<acuity<<std::endl;
            m_acuity = acuity;
        }
        void YarpManager::setBrightness(int brightness) {
            std::cout<<"** Brightness updated. Old: "<<m_brightness<<" New: "<<brightness<<std::endl;
            m_brightness = brightness;
        }

        void YarpManager::setFov(int fov) {
            fov = fov%101;
            if(fov == 0) fov++;
            
            std::cout<<"** FOV updated. Old: "<<m_fov<<"% New: "<<fov<<"%"<<std::endl;
            m_fov = fov;
        }

        void YarpManager::setTreshold(int threshold) {
            if(threshold<0) threshold = threshold*-1;
            std::cout<<"** Threshold updated. Old: "<<m_threshold<<" New: "<<threshold<<std::endl;
            m_threshold = threshold;
        }




    }
}
