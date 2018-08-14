#pragma once

namespace Glue {

using ShortBitMask = short;
using IntBitMask = int;
using BitPos = int;

#if defined(BT_USE_DOUBLE_PRECISION)
using Scalar = double;
#else
using Scalar = float;
#endif

using IntColor = unsigned int;

namespace Constants
{
    constexpr Scalar TAU = 6.283185;
    constexpr IntBitMask AllFilter = 65535;
    constexpr IntBitMask CameraFilter = 64;
    constexpr Scalar FrameSeconds = Scalar(1) / Scalar(64);
    constexpr Scalar timeStep = FrameSeconds;
    constexpr BitPos mouseDraggableBitPos  = 31;
    constexpr IntBitMask mouseDraggableBitMask = (1 << 31);
}

}
