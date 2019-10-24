#pragma once

#include <string>
#include <stdexcept>

namespace Glue {

    class Object
    {
    public:
        bool hasProto(std::string proto) const
        {
            throw std::logic_error("Not implemented");
        }

        template <typename T>
        void setSlot(T const&)
        {
            throw std::logic_error("Not implemented");
        }
    };

}