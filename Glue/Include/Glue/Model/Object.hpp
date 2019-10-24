#pragma once

#include <string>
#include <stdexcept>

namespace Glue {

    class Object
    {
    public:
        virtual bool hasProto(std::string proto) const = 0;

        template <typename T>
        void setSlot(T const&)
        {
            throw std::logic_error("Not implemented");
        }
    };

}