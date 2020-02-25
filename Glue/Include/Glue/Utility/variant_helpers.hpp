#pragma once

#include <vector>
#include <variant>
#include <stdexcept>

namespace Glue
{
    template <typename T>
    struct AttributeFinder
    {
        T* result = nullptr;

        void operator()(T* value)
        {
            if (result)
                throw std::logic_error("More than one attribute of this type is present.");

            result = value;
        }

        template <typename U>
        void operator()(U*)
        {
            // do nothing
        }
    };

    template <typename T, typename A>
    T* find_attribute(std::vector<A> const& attrs)
    {
        AttributeFinder<T> v;
        for (auto a : attrs)
            std::visit(v, a);
        return v.result;
    }
}
