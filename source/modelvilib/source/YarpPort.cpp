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
            std::string address = YarpPort::getSuffix()+m_portName;
            
            std::cout<<"[YARP] Opening a new port"<<std::endl;
            std::cout<<"    * "<<address<<std::endl;
            m_port.open(address.c_str());
            m_port.setStrict();
            m_port.useCallback(*this);
        }
        yarp::os::Bottle& YarpPort::getBottle()
        {
            return m_port.prepare();
        }
        void YarpPort::write()
        {
            m_port.writeStrict();
        }
        void YarpPort::attachNewParameter(std::string parameterName, IParameter* callback)
        {
            m_parameterCallback[parameterName] = callback;
            std::cout << "[YARP][port: "<<m_portName<<"]"<<" new parameter listener ("<<parameterName<<")"<<std::endl;
        }
        void YarpPort::onRead(yarp::os::Bottle& b)
        {
            
            std::string name = b.get(0).asString().c_str();
            if(m_parameterCallback.find(name) != m_parameterCallback.end())
                (*m_parameterCallback[name]).onBottle(m_portName, b);
            
            // Send to all listeners
            for(unsigned int i =0; i<m_listeners.size();i++)
                (m_listeners.at(i))->onBottle(m_portName, b);
        }
        
        void YarpPort::attachListener(IParameter *callback)
        {
            m_listeners.push_back(callback);
            std::cout << "[YARP][port: "<<m_portName<<"]"<<" Listener attached"<<std::endl;
        }
        void YarpPort::detachListener(IParameter *callback)
        {
            for( std::vector<IParameter*>::iterator it = m_listeners.begin(); it!=m_listeners.end(); it++)
            {
                if ((*it) == callback)
                    m_listeners.erase(it);
            }
            std::cout << "[YARP][port: "<<m_portName<<"]"<<" Listener detached"<<std::endl;
        }
        void YarpPort::detachParameterFrom(IParameter *callback)
        {
            std::map<std::string, IParameter*>::iterator parameter;
            for(parameter=m_parameterCallback.begin(); parameter != m_parameterCallback.end(); parameter++ )
            {
                if((*parameter).second != callback)
                    continue;
                
                m_parameterCallback.erase(parameter);
                std::cout << "[YARP][port: "<<m_portName<<"]"<<"Parameter as been erased ("<<(*parameter).first<<")"<<std::endl;
            }
        }
        
        std::string YarpPort::m_suffix = "/target/";
        std::string YarpPort::getSuffix()
        {
            return YarpPort::m_suffix;
        }
        
        void YarpPort::setSuffix(std::string suffix)
        {
            YarpPort::m_suffix = suffix;
        }
    }
}
