#pragma once

#include <memory>

namespace Glue { namespace Avatar {

class KeyInputs
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    KeyInputs();
    ~KeyInputs();
    void update(Node* player, EET_KEY_INPUT_EVENT events);
};

}}
