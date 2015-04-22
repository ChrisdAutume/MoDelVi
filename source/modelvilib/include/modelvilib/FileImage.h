/* 
 * File:   FileImage.h
 * Author: ced13
 *
 * Created on 17 April 2015, 12:13
 */

#ifndef FILEIMAGE_H
#define	FILEIMAGE_H

#include <modelvilib/AbstractImage.h>
#include <iostream>
#include <string>

namespace MoDelVi
{
    namespace Acquisition
    {
        class MODELVI_API FileImage: public AbstractImage
        {
            std::string m_filename;
            void loadFile();
        public:
            FileImage(std::string filename);
            std::string getFilename();;
            void reLoadData();
        };
    }
}
#endif	/* FILEIMAGE_H */
