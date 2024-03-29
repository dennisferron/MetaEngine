#pragma once

#include <functional>
#include <memory>

namespace Glue { namespace EditorGUI {

class Toolbar
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    Toolbar();
    ~Toolbar();
};

}}
