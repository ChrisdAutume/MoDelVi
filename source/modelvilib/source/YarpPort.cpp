//
//  YarpPort.cpp
//  Project
//
//  Created by Christian d'Autume on 11/05/2015.
//
//

#include <modelvilib/YarpPort.h>

namespace MoDelVi {
    namespace Yarp
    {
        YarpPort::YarpPort(std::string portName)
        {
            m_portName = portName;
            std::string address = "/target/"+m_portName;
            
            std::cout<<"- Opening YARP port"<<std::endl;
            std::cout<<"    * "<<address<<std::endl;
            m_port.open(address.c_str());
            m_port.setStrict();
            m_port.useCallback(*this);
        }
        void YarpPort::attachNewParameter(std::string parameterName, ModelVi::Yarp::IParameter* callback)
        {
            if(m_parameterCallback.find(parameterName) == m_parameterCallback.end())
            {
                std::cout << "[YARP][port: "<<m_portName<<"]"<<"Parameter name already used ("<<parameterName<<")"<<std::endl;
            }
            m_parameterCallback[parameterName] = callback;
            std::cout << "[YARP][port: "<<m_portName<<"]"<<" new parameter declared ("<<parameterName<<")"<<std::endl;
        }
        void YarpPort::onRead(yarp::os::Bottle& b)
        {
            std::string name = b.get(0).asString().c_str();
            if(m_parameterCallback.find(name) == m_parameterCallback.end())
               {
                   std::cout << "[YARP][port: "<<m_portName<<"]"<<"No parameter match ("<<name<<")"<<std::endl;
                   return;
               }
            (*m_parameterCallback[name]).onBottle(name, b);
        }
        
        void YarpPort::detachParameterFrom(ModelVi::Yarp::IParameter *callback)
        {
            std::map<std::string, ModelVi::Yarp::IParameter*>::iterator parameter;
            for(parameter=m_parameterCallback.begin(); parameter != m_parameterCallback.end(); parameter++ )
            {
                if((*parameter).second != callback)
                    continue;
                
                m_parameterCallback.erase(parameter);
                std::cout << "[YARP][port: "<<m_portName<<"]"<<"Parameter as been erased ("<<(*parameter).first<<")"<<std::endl;
            }
        }
    }
}
