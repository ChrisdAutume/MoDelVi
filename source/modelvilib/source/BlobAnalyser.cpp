/* 
 * File:   BlobAnalyser.cpp
 * Author: chris
 * 
 * Created on 6 mai 2015, 01:12
 */

#include <modelvilib/BlobAnalyser.h>


/*! \namespace MoDelVi
 * 
 * Lib namespace.
 */
namespace MoDelVi
{

    namespace Analyse
    {
        BlobAnalyser::BlobAnalyser() {
            m_attachedImg = NULL;
        }

        cv::Mat* BlobAnalyser::getResultMat() {
            return &m_matResult;
        }

        void BlobAnalyser::proceed(Acquisition::AbstractImage* img) {
            m_attachedImg = img;
            proceed();
        }

        void BlobAnalyser::proceed() {
            m_match.clear();
            m_attachedImg->getMatImage()->copyTo(m_matResult);
            
            Acquisition::ColorFilter* filteredImg = dynamic_cast<Acquisition::ColorFilter*>(m_attachedImg);
            if(filteredImg) detectBlob(filteredImg);
            else proceedOnAllColor();
            
            // Basic motion detection
            if(m_lastMatch.size()>0)
                basicMotionDetection();
            
            
            m_lastMatch.clear();
            m_lastMatch = m_match;
        }
        
        void BlobAnalyser::proceedOnAllColor()
        {
            Acquisition::ColorFilter* filteredImage = NULL;
            for(int c = (int)Acquisition::ColorFilter::RED_LOW; c<=(int)Acquisition::ColorFilter::YELLOW; c++)
            {
                filteredImage = new Acquisition::ColorFilter(m_attachedImg, (Acquisition::ColorFilter::m_color)c);
                detectBlob(filteredImage);
                delete filteredImage;
            }
                
        }
        
        void BlobAnalyser::detectBlob(Acquisition::ColorFilter* image)
        {
            cv::SimpleBlobDetector detector;
            std::vector<cv::KeyPoint> keypoint;
            
            cv::Mat imgSource = *image->getMatImage();
            cv::bitwise_not(imgSource,imgSource);
            detector.detect(imgSource, keypoint);
            
            
            for(unsigned int i=0; i<keypoint.size(); i++)
            {
                cv::Point relativePt = m_attachedImg->calcFromRelativePoint(keypoint.at(i).pt);
                //Filter
                m_match.push_back(new BlobMatch(relativePt,keypoint.at(i).size*180,image->getColor()));
            }
            
            cv::drawKeypoints( m_matResult,keypoint, m_matResult, image->getBorderColor(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        }
        std::vector<yarp::os::Bottle> BlobAnalyser::getBottleResult(Yarp::YarpPort& outport) {
            std::vector<yarp::os::Bottle> result;
            for(unsigned int i=0; i<m_match.size(); i++)
                result.push_back(m_match.at(i)->getYarpBottle(outport));
            for(unsigned int i=0; i<m_motionMatch.size(); i++)
                result.push_back(m_motionMatch.at(i)->getYarpBottle(outport));
            
            m_motionMatch.clear();
            m_match.clear();
            return result;
        }

        std::vector<BlobMatch*> BlobAnalyser::basicMotionDetection() {
            std::vector<BlobMatch*> notNoise;
            
            for(unsigned int i =0; i<m_lastMatch.size(); i++)
            {
                BlobMatch *oldObj = m_lastMatch.at(i);
                for(unsigned int j = 0; j<m_match.size(); j++)
                {
                    BlobMatch *newObj = m_match.at(j);
                    
                    if(oldObj->color != newObj->color) continue;
                    int distance = (oldObj->pt.x - newObj->pt.x)*(oldObj->pt.x - newObj->pt.x) + (oldObj->pt.y - newObj->pt.y)*(oldObj->pt.y - newObj->pt.y);
                    distance = std::sqrt(distance);
                    // So much for be the same obj
                    if(distance > 10) continue;
                    notNoise.push_back(newObj);
                    
                    //No motion
                    if(distance == 0) continue;
                    if(distance <= 1) continue;
                    m_motionMatch.push_back(new MotionMatch(oldObj->pt, newObj->pt, 0));
                }
            }
            
            return notNoise;
        }

        BlobAnalyser::~BlobAnalyser() {
            m_match.clear();
        }




    }
}
