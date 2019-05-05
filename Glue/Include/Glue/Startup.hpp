#pragma once

#include <string>
#include <memory>

namespace Glue {

class Startup
{
public:

    Startup();
    ~Startup();
    void add_components();

private:

    struct Impl;

    std::unique_ptr<Startup::Impl> impl;
};

}
