#include "Glue/Avatar/Camera.hpp"

namespace Glue { namespace Avatar {

    Camera::Camera()
        : node(nullptr)
    {

    }

    void Camera::setLockTo(Glue::Node* node)
    {
        this->node = node;
    }

}}
