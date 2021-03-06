# The ZLIB license
#
# Copyright (c) 2015 Andre Netzeband
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#

SET (IRRLICHT_STATIC_LIBRARY ON CACHE BOOL "Enabled static lib build.")

if (IRRLICHT_STATIC_LIBRARY)
	message(STATUS "Build static library...")

	if (MSVC_LIKE_COMPILER)
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_IRR_STATIC_LIB_")
		SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D_IRR_STATIC_LIB_")
    else ()
        SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_IRR_STATIC_LIB_")
        SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_IRR_STATIC_LIB_")
	endif ()

else ()
	message(STATUS "Build shared library...")
endif ()
