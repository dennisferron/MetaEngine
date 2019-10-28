#pragma once

#include <utility>

namespace Glue
{

    template<typename T>
    struct symbol
    {
        int id;
        using value_type = T;
    };

    template<typename Base, typename... Ts>
    class variant_ptr
    {
    private:
        struct WrapperBase
        {
            virtual ~WrapperBase() {}
            virtual WrapperBase* clone() const = 0;
            virtual Base* value_ptr() = 0;
            virtual Base const* value_ptr() const = 0;
        };

        template <typename T>
        struct wrapper : WrapperBase
        {
            T value;

            wrapper(T const& value) :
                value(value) {}

            wrapper(T && value) :
                    value(std::move(value)) {}

            WrapperBase* clone() const override
            {
                return new wrapper(value);
            }

            Base* value_ptr() override
            {
                return &value;
            }

            Base const* value_ptr() const override
            {
                return &value;
            }
        };

        int tag;
        WrapperBase* ptr;

    public:
        // Empty
        variant_ptr() : tag(-1), ptr(nullptr)
        {
        }

        template<typename T>
        variant_ptr(symbol<T> const& tag, T&& value) :
            tag(tag.id),
            ptr(new wrapper<T> (std::move(value)))
        {
        }

        template<typename T>
        variant_ptr(symbol<T> const& tag, T const& value) :
                tag(tag.id),
                ptr(new wrapper<T> (value))
        {
        }

        variant_ptr(variant_ptr&& that) :
            tag(that.tag),
            ptr(that.ptr)
        {
            that.tag = -1;
            that.ptr = nullptr;
        }

        variant_ptr(variant_ptr const& that) :
            tag(that.tag),
            ptr(that.ptr->clone())
        {
        }

        ~variant_ptr()
        {
            delete ptr;
        }

        variant_ptr& operator =(variant_ptr const& that)
        {
            delete ptr;

            tag = that.tag;
            ptr = that.ptr->clone();
        }

        variant_ptr& operator =(variant_ptr&& that)
        {
            delete ptr;

            tag = that.tag;
            ptr = that.ptr;

            that.tag = -1;
            that.ptr = nullptr;
        }

        Base& operator * ()
        {
            return *(ptr->value_ptr());
        }

        Base const& operator * () const
        {
            return *(ptr->value_ptr());
        }

        Base* operator -> ()
        {
            return ptr->value_ptr();
        }

        Base const* operator -> () const
        {
            return ptr->value_ptr();
        }
    };
}
