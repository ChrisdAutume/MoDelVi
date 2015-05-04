/* 
 * File:   CamYarp.cpp
 * Author: chris
 * 
 * Created on 4 mai 2015, 03:19
 */

#include "modelvilib/CamYarp.h"

namespace MoDelVi
{
    namespace Manager
    {

        CamYarp::CamYarp(std::string name, int* acuity, int* fov, int* brightness, int* threshold) {
            m_name = name;
            m_acuity = acuity;
            m_fov = fov;
            m_brightness = brightness;
            m_threshold = threshold;
            
            std::string suffix = "/target/"+name+"/";
            
            std::cout<<"## "<<name<<" cam initialisation ##"<<std::endl;
            std::cout<<"- Opening YARP port"<<std::endl;
            std::cout<<"    * "<<suffix<<"in"<<std::endl;
            m_inPort.open(suffix+"in");
            m_inPort.setStrict();
            m_inPort.setReader(*this);
            std::cout<<"    * "<<suffix<<"out"<<std::endl;
            m_outPort.open(suffix+"out");
            m_outPort.setStrict();
            std::cout<<"    * "<<suffix<<"data"<<std::endl;
            m_dataPort.open(suffix+"data");
            m_dataPort.setStrict();
        }

        bool CamYarp::read(yarp::os::ConnectionReader& connection) {
            std::cout<<"["<<m_name<<" camera] Receiving things. ";
            
            if(connection.isTextMode())
            {
                std::cout<<"ERROR: Text mode"<<std::endl;
                return false;
            }
            yarp::sig::ImageOf<yarp::sig::PixelRgb> *image = new yarp::sig::ImageOf<yarp::sig::PixelRgb>();
            bool ok = image->read(connection);
            if (!ok) 
            {
                return false;
                std::cout<<"INCORRECT DATA"<<std::endl;
            }else std::cout<<"PROCESSING"<<std::endl;
            // process data in b
            return true;
            //std::cout<<"[IMAGE] receveid should be an image. size: "<<b.width()<<" x "<<b.height()<<std::endl;
        }
        CamYarp::~CamYarp() {
        }
    }
}

