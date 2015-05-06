/* 
 * File:   AbstractAnalyser.cpp
 * Author: ced13
 * 
 * Created on 22 April 2015, 12:17
 */

#include <modelvilib/AbstractAnalyser.h>

namespace MoDelVi
{
    namespace Analyse
    {
        AbstractAnalyser::AbstractAnalyser()
        :m_attachedImg(NULL)
        {
        }

        void AbstractAnalyser::setNewImage(Acquisition::AbstractImage* img) {
            m_attachedImg = img;
        }

    }
}
