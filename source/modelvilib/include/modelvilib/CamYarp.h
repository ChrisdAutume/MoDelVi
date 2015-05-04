/* 
 * File:   CamYarp.h
 * Author: chris
 *
 * Created on 4 mai 2015, 03:19
 */

#ifndef CAMYARP_H
#define	CAMYARP_H

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <iostream>
#include <vector>
#include <string>

namespace MoDelVi
{
    namespace Manager
    {
        class CamYarp {
        public:
            CamYarp(std::string name, int* acuity, int* fov, int* brightness, int* threshold);
            virtual ~CamYarp();
            void frame();
            
        private:
            std::string m_name;
            
            int *m_acuity;
            int *m_fov;
            int *m_brightness;
            int *m_threshold;
            
            yarp::os::BufferedPort<yarp::os::Bottle> m_inPort;
            yarp::os::BufferedPort<yarp::os::Bottle> m_outPort;
            yarp::os::BufferedPort<yarp::os::Bottle> m_dataPort;

        };
    }
}

#endif	/* CAMYARP_H */

