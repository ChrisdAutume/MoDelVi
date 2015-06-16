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
        /*!
         @class FileImage
         @brief Loading image from disk
         */
        class MODELVI_API FileImage: public AbstractImage
        {
            //! Path to the image
            std::string m_filename;
            
            //! Load the file
            void loadFile();
        public:
            //! @param filename Path to the image to load
            FileImage(std::string filename);
            std::string getFilename();
            
            //! Reload the file from the disk
            void reLoadData();
        };
    }
}
#endif	/* FILEIMAGE_H */
