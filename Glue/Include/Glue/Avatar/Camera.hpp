#pragma once

namespace Glue {
    class Node;
}

namespace Glue { namespace Avatar {

class Camera
{
private:
    Node* node;

public:
    Camera();
    void setLockTo(Node* node);
};

}}
