#pragma once

#include <modelvilib/fiblib_api.h>

namespace fiblib
{
    /** \brief ..

    ...
    */
    class FIBLIB_API Fibonacci
    {
    public:
        Fibonacci();
        virtual ~Fibonacci();

        unsigned int operator()(unsigned int i);
    };

} // namespace fiblib
