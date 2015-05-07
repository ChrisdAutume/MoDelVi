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

        BlobAnalyser::BlobAnalyser(Acquisition::AbstractImage* img) {
            m_attachedImg = img;
        }

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
            cv::SimpleBlobDetector detector;
            std::vector<cv::KeyPoint> keypoint;
            
            //cv::Mat imgSource (m_attachedImg->getIplImage());
            cv::Mat imgSource = *m_attachedImg->getMatImage();
            
            detector.detect(imgSource, keypoint);
            
            
            for(unsigned int i=0; i<keypoint.size(); i++)
            {
                cv::Point relativePt = m_attachedImg->calcFromRelativePoint(keypoint.at(i).pt);
                cv::Rect roi(keypoint.at(i).pt.x - (keypoint.at(i).size/4),keypoint.at(i).pt.y + (keypoint.at(i).size/4),(keypoint.at(i).size/2)*std::sqrt(2),(keypoint.at(i).size/2)*std::sqrt(2));
                m_match.push_back(new BlobMatch(relativePt,keypoint.at(i).size*180,getColor(roi)));
            }
            cv::drawKeypoints( imgSource,keypoint, m_matResult, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
            
            // Basic motion detection
            if(m_lastMatch.size()>0)
                basicMotionDetection();
            
            m_lastMatch.clear();
            m_lastMatch = m_match;
        }

        std::string BlobAnalyser::getColor(cv::Rect roi) {
            std::string result;
            cv::Mat img_roi = (*(m_attachedImg->getMatImage()))(roi);
            cv::Scalar avgPixelIntensity = cv::mean( img_roi );
            
            int r = (int)avgPixelIntensity[2], g= (int)avgPixelIntensity[1], b = (int)avgPixelIntensity[0];
            
            if(r>200 && b<100 && g<100) result = "red";
            else if(g>200 && b<100 && r<100) result = "green";
            else if(b>200 && g<100 && r<100) result = "blue";
            else std::string result("any");
            return result;
        }

        std::vector<yarp::os::Bottle> BlobAnalyser::getBottleResult(yarp::os::BufferedPort<yarp::os::Bottle>& outport) {
            std::vector<yarp::os::Bottle> result;
            for(unsigned int i=0; i<m_match.size(); i++)
                result.push_back(m_match.at(i)->getYarpBottle(outport));
            for(unsigned int i=0; i<m_motionMatch.size(); i++)
                result.push_back(m_motionMatch.at(i)->getYarpBottle(outport));
            
            return result;
        }

        void BlobAnalyser::basicMotionDetection() {
            m_motionMatch.clear();
            for(unsigned int i =0; i<m_lastMatch.size(); i++)
            {
                BlobMatch *oldObj = m_lastMatch.at(i);
                for(unsigned int j = 0; j<m_match.size(); j++)
                {
                    BlobMatch *newObj = m_match.at(j);
                    
                    if(oldObj->color != newObj->color) continue;
                    int distance = (oldObj->pt.x - newObj->pt.x)*(oldObj->pt.x - newObj->pt.x) + (oldObj->pt.y - newObj->pt.y)*(oldObj->pt.y - newObj->pt.y);
                    distance = std::sqrt(distance);
                    
                    //No motion
                    if(distance == 0) continue;
                    // So much for be the same obj
                    if(distance > 10) continue;
                    m_motionMatch.push_back(new MotionMatch(oldObj->pt, newObj->pt, 0));
                }
            }
        }

        BlobAnalyser::~BlobAnalyser() {
            //m_matResult.deallocate();
            m_match.clear();
        }




    }
}
