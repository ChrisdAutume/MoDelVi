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
        cv::Mat* BlobAnalyser::getResultMat() {
            return &m_matResult;
        }

        void BlobAnalyser::proceed() {
            cv::SimpleBlobDetector detector;
            std::vector<cv::KeyPoint> keypoint;
            
            cv::Mat imgSource(m_attachedImg->getIplImage());
            
            detector.detect(imgSource, keypoint);
            
            for(int i=0; i<keypoint.size(); i++)
            {
                cv::Point relativePt = m_attachedImg->calcFromRelativePoint(keypoint.at(i).pt);
                m_match.push_back(new BlobMatch(keypoint.at(i).pt,keypoint.at(i).size,getColor(keypoint.at(i).pt)));
                std::cout<<"Blob match: x:"<<relativePt.x<<" y:"<<relativePt.y<<" Size:"<<keypoint.at(i).size<<" Couleur: "<<getColor(keypoint.at(i).pt)<<std::endl;
            }
            cv::drawKeypoints( imgSource,keypoint, m_matResult, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        }

        std::string BlobAnalyser::getColor(cv::Point point) {
            std::string result("any");
            
            cv::Mat img(m_attachedImg->getIplImage());
            cv::Vec3b bgrPixel = img.at<cv::Vec3b>(point.x,point.y);
            std::cout<<"B: "<<(int)bgrPixel[0]<<" G:"<<(int)bgrPixel[1]<<" R:"<<(int)bgrPixel[2]<<std::endl;
            return result;
        }

        std::vector<yarp::os::Bottle> BlobAnalyser::getBottleResult(yarp::os::BufferedPort<yarp::os::Bottle>& outport) {
            std::vector<yarp::os::Bottle> result;
            for(int i=0; i<m_match.size(); i++)
                result.push_back(m_match.at(i)->getYarpBottle(outport));
            
            return result;
        }



    }
}
