/* 
 * File:   ShapesAnalyser.h
 * Author: ced13
 *
 * Created on 22 April 2015, 12:27
 */

#ifndef SHAPESANALYSER_H
#define	SHAPESANALYSER_H

#include <modelvilib/AbstractAnalyser.h>


/*! \namespace MoDelVi
 * 
 * Lib namespace.
 */
namespace MoDelVi
{
    /*! \namespace Analyse
    * 
    * Namespace for Image analyse procedure.
    */
    namespace Analyse
    {
        /*! \class AbstractAnalyser
        * \brief Abstract class to define basic Analyser
        *
        *  Abstract class to analyse img data.
        */
        class MODELVI_API ShapesAnalyser: public AbstractAnalyser
        {
        protected:
            IplImage* m_greyScale;
            IplImage* m_result;
            int m_grayTreshold;
            
            void filter();
            void findShapes();
            void findShapesUsingCanny();
        public:
            ShapesAnalyser();
            ShapesAnalyser(Acquisition::AbstractImage* img);
            IplImage* getResultIpl() { return m_result;};
            int* getGrayTreshold() { return &m_grayTreshold; };
            virtual void proceed();
            virtual void proceed(Acquisition::AbstractImage* img);


        };
    }
    
}

#endif	/* SHAPESANALYSER_H */

