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

namespace MoDelVi
{
    namespace Yarp
    {
        class YarpPort : public yarp::os::TypedReaderCallback<yarp::os::Bottle>
        {
        public:
            YarpPort(std::string portName);
            void attachNewParameter(std::string parameterName, ModelVi::Yarp::IParameter *callback);
            void detachParameterFrom(ModelVi::Yarp::IParameter *callback);
            virtual void onRead(yarp::os::Bottle& b);
        private:
            std::string m_portName;
            yarp::os::BufferedPort<yarp::os::Bottle> m_port;
            std::map<std::string, ModelVi::Yarp::IParameter*> m_parameterCallback;
        };
    }
    
}

#endif
