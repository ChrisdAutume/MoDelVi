/* 
 * File:   FileImage.cpp
 * Author: ced13
 *
 * Created on 17 April 2015, 12:15
 */

#include <modelvilib/FileImage.h>

namespace MoDelVi
{
    namespace Acquisition
    {

        std::string FileImage::getFilename() {
            return m_filename;
        }
        
        FileImage::FileImage(std::string filename) {
            m_filename = filename;
            loadFile();
        }

        void FileImage::reLoadData() {
            cvReleaseImage(&m_image);
            m_image = NULL;
            m_state = IMAGE_NOLOADED;
            
            loadFile();
        }
       void FileImage::loadFile() {
            m_image = cvLoadImage(m_filename.c_str());
            
            if(m_image && m_image->imageSize>0)
                m_state = IMAGE_LOADED;          
        }
    }
}
