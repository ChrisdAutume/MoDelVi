/* 
 * File:   BlobAnalyser.h
 * Author: chris
 *
 * Created on 6 mai 2015, 01:12
 */

#ifndef BLOBANALYSER_H
#define	BLOBANALYSER_H

#include <modelvilib/AbstractAnalyser.h>
#include <yarp/os/Bottle.h>

#include "BlobMatch.h"


/*! \namespace MoDelVi
 * 
 * Lib namespace.
 */
namespace MoDelVi
{

    namespace Analyse
    {

        class MODELVI_API BlobAnalyser: public AbstractAnalyser
        {
        protected:
            cv::Mat m_matResult;
            std::vector<BlobMatch*> m_match;
            
            std::string getColor(cv::Point point);
        public:
            BlobAnalyser(Acquisition::AbstractImage* img);
            ~BlobAnalyser();
            std::vector<yarp::os::Bottle> getBottleResult(yarp::os::BufferedPort<yarp::os::Bottle>& outport);
            cv::Mat* getResultMat();
            virtual void proceed();

        };
    }
    
}

#endif	/* BLOBANALYSER_H */

