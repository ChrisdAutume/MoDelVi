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
            std::cout<<"    * "<<suffix<<"out"<<std::endl;
            m_outPort.open(suffix+"out");
            m_outPort.setStrict();
            std::cout<<"    * "<<suffix<<"data"<<std::endl;
            m_dataPort.open(suffix+"data");
            m_dataPort.setStrict();
        }

        void CamYarp::frame() {
            yarp::sig::ImageOf < yarp::sig::PixelRgb > *image = new yarp::sig::ImageOf < yarp::sig::PixelRgb >();
            image = m_inPort.read();
            if (image!=NULL) {
                std::cout<<"["<<m_name<<" camera] Image receiving: "<<image->height()<<"x"<<image->width()<<std::endl;
            }
        }

        CamYarp::~CamYarp() {
        }
    }
}

