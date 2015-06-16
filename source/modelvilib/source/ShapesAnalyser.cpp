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

        ShapesAnalyser::ShapesAnalyser(): AbstractAnalyser()
        {
            m_grayTreshold = 150;
            //m_result = cvCreateImage(cvGetSize(m_attachedImg->getIplImage()),IPL_DEPTH_8U, 3);
            //cvZero(m_result);
            m_greyScale = NULL;
        }
        ShapesAnalyser::ShapesAnalyser(Acquisition::AbstractImage* img)
        :AbstractAnalyser(img),
        m_grayTreshold(150)
        {            
            // Create result IMG
            //m_result = cvCreateImage(cvGetSize(m_attachedImg->getOriginalIplImage()),IPL_DEPTH_8U, 3);
            //cvZero(m_result);
            m_greyScale = NULL;
        }

        void ShapesAnalyser::proceed() {
            
            
            //cvReleaseImage(&m_result);
            if(m_greyScale)
                cvReleaseImage(&m_greyScale);
            //m_result = cvCloneImage(m_attachedImg->getIplImage());
            
            m_greyScale = m_attachedImg->getIplImage();
            
            //filter();
            findShapes();
            //findShapesUsingCanny();
            //m_result = m_greyScale;
        }

        void ShapesAnalyser::filter() {
            
            //cvSmooth(m_attachedImg->getIplImage(), m_attachedImg->getIplImage(), CV_GAUSSIAN,3,3); 
            m_greyScale = cvCreateImage(cvGetSize(m_attachedImg->getIplImage()), 8, 1); 
            cvCvtColor(m_attachedImg->getIplImage(),m_greyScale,CV_BGR2GRAY);
            cvThreshold(m_greyScale,m_greyScale,m_grayTreshold,255,CV_THRESH_BINARY_INV);
        }

        void ShapesAnalyser::findShapesUsingCanny() {
            cv::Mat grey = *m_attachedImg->getMatImage();
            cv::Canny(grey,grey, 100, 200, 3);
            
            //Find contour
            std::vector<std::vector<cv::Point> > contours;
            std::vector<cv::Vec4i> hierarchy;
            
            cv::RNG rng(12345);
            cv::findContours(grey, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
            
            cv::Mat draw = *m_attachedImg->getOriginalMatImage();
            
            int nbPts = 4;
            for( int i = 0; i< (int)contours.size(); i++ )
            {
                std::cout<<"Contours n°"<<i<<" nb:"<<contours[i].size()<<std::endl;
               //cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
               //cv::drawContours( draw, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
                for(int j = 0; j < nbPts; j++)
                {
                    int idPt = (contours.at(i).size()/(float)nbPts)*j;
                    std::cout<<"Pt n°"<<idPt<<std::endl;
                    cv::Point Pt = contours.at(i).at(idPt);
                    cv::circle(draw, Pt, 5, cvScalar(0,255,0));
                }
            }
            
            cv::imshow( "Canny edge detection", draw );
             
        }
        

        void ShapesAnalyser::findShapes() {
            CvSeq* contour;
            CvSeq* result;
            CvMemStorage *storage = cvCreateMemStorage(0);
            
            cv::Mat draw = *m_attachedImg->getOriginalMatImage();
            
            //finding all contours in the image
            cvFindContours(m_greyScale, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
            
            while(contour)
            {
                //obtain a sequence of point
                result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);
                std::cout<<"Contours  nb:"<<result->total<<std::endl;
                if(result->total>=4 )
                {
                    //iterating through each point
                    CvPoint *pt[4];
                    for(int i=0;i<4;i++){
                        pt[i] = (CvPoint*)cvGetSeqElem(result, i);
                        cv::circle(draw, cv::Point(pt[i]->x,pt[i]->y), 10, cvScalar(0,255,0));
                        std::cout<<"Pt x:"<<pt[i]->x<<" y:"<<pt[i]->y<<std::endl;
                    }

                    //drawing lines around the quadrilateral
                    cvLine(m_result, *pt[0], *pt[1], cvScalar(0,255,0),4);
                    cvLine(m_result, *pt[1], *pt[2], cvScalar(0,255,0),4);
                    cvLine(m_result, *pt[2], *pt[3], cvScalar(0,255,0),4);
                    cvLine(m_result, *pt[3], *pt[0], cvScalar(0,255,0),4);
                    
                    
                }
                 contour = contour->h_next; 
                
            }
            cv::imshow( "Point shapes", draw );
        }

        void ShapesAnalyser::proceed(Acquisition::AbstractImage* img) {
            m_attachedImg = img;
            proceed();
        }

    }
}
