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

namespace ModelVi
{
    namespace Yarp
    {
         class IParameter
        {
        public:
            virtual void onBottle(std::string parameterName, yarp::os::Bottle &b) =0;
        };
    }
}

#endif
