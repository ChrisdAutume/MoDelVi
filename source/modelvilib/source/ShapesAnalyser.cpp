/* 
 * File:   ShapesAnalyser.cpp
 * Author: ced13
 * 
 * Created on 22 April 2015, 12:27
 */

#include <modelvilib/ShapesAnalyser.h>

namespace MoDelVi
{
    namespace Analyse
    {

        ShapesAnalyser::ShapesAnalyser(): AbstractAnalyser() {
        }
        ShapesAnalyser::ShapesAnalyser(Acquisition::AbstractImage* img)
        :AbstractAnalyser(img)
        {
            if(m_attachedImg->isLoaded())
                std::cout<<"Img loaded by shapes class"<<std::endl;
            
            // Create result IMG
            m_result = cvCreateImage(cvGetSize(m_attachedImg->getIplImage()),IPL_DEPTH_8U, 3);
            cvZero(m_result);
        }

        void ShapesAnalyser::proceed() {
            cvCopy(m_attachedImg->getIplImage(), m_result);
            filter();
            findShapes();
            findShapesUsingCanny();
            //m_result = m_greyScale;
        }

        void ShapesAnalyser::filter() {
            //cvSmooth(m_attachedImg->getIplImage(), m_attachedImg->getIplImage(), CV_GAUSSIAN,3,3); 
            m_greyScale = cvCreateImage(cvGetSize(m_attachedImg->getIplImage()), 8, 1); 
            cvCvtColor(m_attachedImg->getIplImage(),m_greyScale,CV_BGR2GRAY);
        }

        void ShapesAnalyser::findShapesUsingCanny() {
            cv::Mat grey(m_greyScale);
            cv::Mat greyT(m_greyScale);
            cv::imshow( "Grey img", greyT );
            cv::Canny(grey,grey, 100, 200, 3);
            
            //Find contour
            std::vector<std::vector<cv::Point>> contours;
            std::vector<cv::Vec4i> hierarchy;
            
            cv::RNG rng(12345);
            cv::findContours(grey, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
            cv::Mat draw = cv::Mat::zeros(grey.size(), CV_8UC3);
            
            for( int i = 0; i< (int)contours.size(); i++ )
            {
               cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
               cv::drawContours( draw, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
            }
            cv::imshow( "Canny edge detection", draw );
           
        }

        void ShapesAnalyser::findShapes() {
            CvSeq* contour;
            CvSeq* result;
            CvMemStorage *storage = cvCreateMemStorage(0);
            
            //Treshold Gray
            cvThreshold(m_greyScale,m_greyScale,100,255,CV_THRESH_BINARY_INV);
            //finding all contours in the image
            cvFindContours(m_greyScale, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
            
            while(contour)
            {
                //obtain a sequence of point
                result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);
                
                if(result->total==4 )
{
                    //iterating through each point
                    CvPoint *pt[4];
                    for(int i=0;i<4;i++){
                    pt[i] = (CvPoint*)cvGetSeqElem(result, i);
                    }

                    //drawing lines around the quadrilateral
                    cvLine(m_result, *pt[0], *pt[1], cvScalar(0,255,0),4);
                    cvLine(m_result, *pt[1], *pt[2], cvScalar(0,255,0),4);
                    cvLine(m_result, *pt[2], *pt[3], cvScalar(0,255,0),4);
                    cvLine(m_result, *pt[3], *pt[0], cvScalar(0,255,0),4);
                }
                 contour = contour->h_next; 
                
            }
        }
    }
}
