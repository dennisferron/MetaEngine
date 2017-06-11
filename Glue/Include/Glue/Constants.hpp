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

struct Constants
{
    static constexpr Scalar TAU = 6.283185;
    static constexpr IntBitMask AllFilter = 65535;
    static constexpr IntBitMask CameraFilter = 64;
    static constexpr Scalar FrameSeconds = Scalar(1) / Scalar(64);
    static constexpr Scalar timeStep = FrameSeconds;
    static constexpr BitPos mouseDraggableBitPos  = 31;
    static constexpr IntBitMask mouseDraggableBitMask = (1 << 31);
};

}
