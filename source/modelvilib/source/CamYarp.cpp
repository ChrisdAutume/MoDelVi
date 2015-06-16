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
            
            std::string suffix = Yarp::YarpPort::getSuffix()+name+"/";
            
            std::cout<<"## "<<name<<" cam initialisation ##"<<std::endl;
            std::cout<<"- Opening YARP port"<<std::endl;
            
            std::cout<<"    * "<<suffix<<"in"<<std::endl;
            std::string full =suffix+"in";
            m_inPort.open(full.c_str());
            m_inPort.setStrict();
            m_inPort.useCallback(*this);
            
            std::cout<<"    * "<<suffix<<"out"<<std::endl;
            full=suffix+"out";
            m_outPort.open(full.c_str());
            m_outPort.setStrict();
            
            // Opening data stream
            m_dataPort = new Yarp::YarpPort(name+"/data");
            m_dataPort->attachListener(this);
            
            //Populate analyser
            m_analyser.push_back(new Analyse::BlobAnalyser);
            m_lastImg = std::clock();
            
            
        }

        void CamYarp::onRead(yarp::sig::ImageOf<yarp::sig::PixelRgb>& b) {

            if(((std::clock() - m_lastImg) / (double)(CLOCKS_PER_SEC / 1000)) > 1)
            {
            Acquisition::YarpImage image(&b);
            
            image.setBlurr(*m_acuity);
            image.setBrightness(*m_brightness);
            image.setFov(*m_fov);
            image.prepareImage();
            
            
            if(image.isLoaded())
            {
		
                for(unsigned int i =0; i<m_analyser.size(); i++)
                {
                    m_analyser.at(i)->proceed(&image);
                    m_analyser.at(i)->getBottleResult(*m_dataPort);
                }

                outputMatImage(*((Analyse::BlobAnalyser*)m_analyser.at(0))->getResultMat());
            }
                m_lastImg = std::clock();
            }      
        }
        void CamYarp::onBottle( std::string portName, yarp::os::Bottle &b)
        {
            if(portName == "module")
                std::cout<<"Bottle received CAM MODULE"<<std::endl;
        }
        void CamYarp::outputMatImage(cv::Mat& img)
        {
            yarp::sig::ImageOf<yarp::sig::PixelBgr>& yarpReturnImage = m_outPort.prepare();
            IplImage OutputIpl = img;
            yarpReturnImage.wrapIplImage(&OutputIpl);
            m_outPort.writeStrict();
        }
        void CamYarp::outputIplImage(IplImage& img)
        {
            yarp::sig::ImageOf<yarp::sig::PixelBgr>& yarpReturnImage = m_outPort.prepare();
            yarpReturnImage.wrapIplImage(&img);
            m_outPort.writeStrict();
        }
        std::vector<Analyse::AbstractAnalyser*>* CamYarp::getAnalyserPtr() {
            return &m_analyser;
        }

        CamYarp::~CamYarp() {
            delete m_dataPort;
        }
    }
}

