//
//  YarpPort.h
//  
//
//  Created by Christian d'Autume on 11/05/2015.
//
//

#ifndef _YarpPort_h
#define _YarpPort_h

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <modelvilib/IParameter.h>
#include <map>
#include <vector>
#include <iostream>

namespace MoDelVi
{
    namespace Yarp
    {
        /*!
         @class YarpPort
         @brief 
         */
        class MODELVI_API YarpPort : public yarp::os::TypedReaderCallback<yarp::os::Bottle>
        {
        public:
            
            static std::string getSuffix();
            static void setSuffix(std::string suffix);
            
            YarpPort(std::string portName);
            void attachListener(IParameter *callback);
            void detachListener(IParameter *callback);
            void attachNewParameter(std::string parameterName, IParameter *callback);
            void detachParameterFrom(IParameter *callback);
            virtual void onRead(yarp::os::Bottle& b);
            
            yarp::os::Bottle& getBottle();
            void write();
        private:
            static std::string m_suffix;
            std::string m_portName;
            yarp::os::BufferedPort<yarp::os::Bottle> m_port;
            std::map<std::string, IParameter*> m_parameterCallback;
            std::vector<IParameter*> m_listeners;
        };
    }
    
}

#endif
