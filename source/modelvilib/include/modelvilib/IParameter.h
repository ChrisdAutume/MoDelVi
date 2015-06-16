//
//  IParameter.h
//  Project
//
//  Created by Christian d'Autume on 11/05/2015.
//
//

#ifndef Project_IParameter_h
#define Project_IParameter_h

#include <yarp/os/all.h>
#include <modelvilib/modelvi_api.h>
#include <iostream>
#include <string>

namespace MoDelVi
{
    namespace Yarp
    {
        /*!
         @class IParameter
         @brief Abstract class for YarpPort callback. Cannot be instanciated.
         */
         class MODELVI_API IParameter
        {
        public:
            virtual void onBottle(std::string parameterName, yarp::os::Bottle &b) =0;
        };
    }
}

#endif
