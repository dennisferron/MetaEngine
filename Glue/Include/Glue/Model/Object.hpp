#pragma once

#include <string>

namespace Glue {

    class Object
    {
    public:
        virtual bool hasProto(std::string proto) const = 0;
    };

}