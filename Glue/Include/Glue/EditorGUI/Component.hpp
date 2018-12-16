#pragma once

#include <memory>

namespace Glue { namespace EditorGUI {

class Component
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    Component();
    ~Component();
};

}}
