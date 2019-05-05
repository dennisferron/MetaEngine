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

if (APPLE)

    SET(CMAKE_MACOSX_RPATH 0)
    SET(CMAKE_MACOSX_BUNDLE_BUNDLE_NAME "IrrlichtExample")

    #cocoa
    #carbon
    #opengl
    #IOKit
    #CoreFoundation
    #Foundation

        #[[ For some reason, FIND_LIBRARY malfunctions for some of these
        and puts a different framework in some of the variables.

            FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    FIND_LIBRARY(IOKIT_LIBRARY IOKit)
    FIND_LIBRARY(FOUNDATION_LIBRARY Foundation)
    FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation)

    list(APPEND OS_DEPENDENT_LIBRARIES
            ${COCOA_LIBRARY}
            ${CARBON_LIBRARY}
            ${IOKIT_LIBRARY}
            ${FOUNDATION_LIBRARY}
            ${COREFOUNDATION_LIBRARY}
            /System/Library/Frameworks/IOKit.framework
            /System/Library/Frameworks/Foundation.framework
            )
]]

        # Full path gets turned into "-framework foo"
    list(APPEND OS_DEPENDENT_LIBRARIES
            /System/Library/Frameworks/Cocoa.framework
            /System/Library/Frameworks/Carbon.framework
            /System/Library/Frameworks/IOKit.framework
            /System/Library/Frameworks/CoreFoundation.framework
            /System/Library/Frameworks/Foundation.framework
        )

    SET(OS_SOURCE_FILES
            #source/Irrlicht/MacOSX/CIrrDeviceMacOSX.mm
            #source/Irrlicht/MacOSX/OSXClipboard.mm
            #source/Irrlicht/MacOSX/AppDelegate.mm
            source/Irrlicht/COSOperator.mm
            source/Irrlicht/CIrrDeviceOSX.mm
            source/Irrlicht/CNSOGLManager.mm
            source/Irrlicht/Irrlicht.mm
            )

    SET(OS_HEADER_FILES
            #source/Irrlicht/MacOSX/AppDelegate.h
            #source/Irrlicht/MacOSX/CIrrDeviceMacOSX.h
            source/Irrlicht/CIrrDeviceOSX.h
            #source/Irrlicht/MacOSX/OSXClipboard.h
            )

    #[[
        INCLUDE_DIRECTORIES(
            source/Irrlicht/MacOSX
        )
    ]]

    if (IRRLICHT_ENABLE_X11_SUPPORT)

        if ("$ENV{HOSTTYPE}" STREQUAL "x86_64")
            LINK_DIRECTORIES(/usr/X11/lib64)
        else ()
            LINK_DIRECTORIES(/usr/X11/lib)
        endif ()
    endif ()

    #else ()
#[[    if (GCC_LIKE_COMPILER)
        SET (CMAKE_STATIC_LINKER_FLAGS
                "${CMAKE_STATIC_LINKER_FLAGS} -framework cocoa -framework carbon -framework opengl -framework IOKit -framework CoreFoundation -framework Foundation"
                )
        SET (CMAKE_SHARED_LINKER_FLAGS
                "${CMAKE_SHARED_LINKER_FLAGS} -framework cocoa -framework carbon -framework opengl -framework IOKit -framework CoreFoundation -framework Foundation"
                )
        SET (CMAKE_MODULE_LINKER_FLAGS
                "${CMAKE_MODULE_LINKER_FLAGS} -framework cocoa -framework carbon -framework opengl -framework IOKit -framework CoreFoundation -framework Foundation"
                )
        SET (CMAKE_EXE_LINKER_FLAGS
                "${CMAKE_EXE_LINKER_FLAGS} -framework cocoa -framework carbon -framework opengl -framework IOKit -framework CoreFoundation -framework Foundation"
                )
]]

#    else ()
#        message(SEND_ERROR "(Configuring framework) I did not have non gcc like compilers in mind, when writing the MacOSX dependent settings... please adapt to your needs!")
#    endif ()

    #endif ()

endif ()