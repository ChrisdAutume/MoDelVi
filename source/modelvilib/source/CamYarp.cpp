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
            std::string full =suffix+"in";
            m_inPort.open(full.c_str());
            m_inPort.setStrict();
            m_inPort.useCallback(*this);
            std::cout<<"    * "<<suffix<<"out"<<std::endl;
            full=suffix+"out";
            m_outPort.open(full.c_str());
            m_outPort.setStrict();
            std::cout<<"    * "<<suffix<<"data"<<std::endl;
            full=suffix+"data";
            m_dataPort.open(full.c_str());
            m_dataPort.setStrict();
            
            m_analyser.push_back(new Analyse::BlobAnalyser);
        }

        void CamYarp::onRead(yarp::sig::ImageOf<yarp::sig::PixelRgb>& b) {
            
            Acquisition::YarpImage image(&b);
            
            image.setBlurr(*m_acuity);
            image.setBrightness(*m_brightness);
            image.setFov(*m_fov);
            image.prepareImage();

            
            //outputIplImage(*image.getIplImage());
            
            if(image.isLoaded())
            {
		
                for(unsigned int i =0; i<m_analyser.size(); i++)
                {
                    m_analyser.at(i)->proceed(&image);
                    m_analyser.at(i)->getBottleResult(m_dataPort);
                }

                outputMatImage(*((Analyse::BlobAnalyser*)m_analyser.at(0))->getResultMat());
            }
            
            
            
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
        }
    }
}

