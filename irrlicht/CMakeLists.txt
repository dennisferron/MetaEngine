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

cmake_minimum_required(VERSION 3.13)

PROJECT(Irrlicht)

list(APPEND CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/CMake
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/Dependencies
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/Compiler
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/OperatingSystems
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/Options
	${CMAKE_CURRENT_SOURCE_DIR}/CMake/Packages
)

# Contains the version information...
INCLUDE(IrrlichtVersion)

# Contains a list of source files...
INCLUDE(IrrlichtSource)

# Load compiler dependent settings...
INCLUDE(CompilerGccLikeSettings)
INCLUDE(CompilerMSVCLikeSettings)

# Load os dependent settings...
INCLUDE(UnixLikeSettings)
INCLUDE(MacOSXSettings)
INCLUDE(WindowsSettings)

# Load option depending settings...
INCLUDE(OptionProfiling)
INCLUDE(OptionDirectX9)
INCLUDE(OptionX11Support)
INCLUDE(OptionStaticLib)
INCLUDE(OptionInstallMediaFiles)

# Generic definitions for all compilers and operating systems...
ADD_DEFINITIONS(	
	-DPNG_THREAD_UNSAFE_OK
	-DPNG_NO_MMX_CODE
	-DPNG_NO_MNG_FEATURES
)

# Add dependency definitions
INCLUDE(DependencyOpenGL)
INCLUDE(DependencyDirectX9)
INCLUDE(DependencyFontConfig)
INCLUDE(DependencyX11)
INCLUDE(DependencyFreeType)

# Print all settings
#INCLUDE(PrintSettings)
#INCLUDE(WriteSettings)

list(APPEND ALL_HEADER_FILES ${OS_HEADER_FILES})


		# Target settings
SET_SOURCE_FILES_PROPERTIES(ALL_HEADER_FILES
		PROPERTIES HEADER_FILE_ONLY TRUE)

LIST(APPEND ALL_SOURCE_FILES ${OS_SOURCE_FILES})
LIST(APPEND ALL_SOURCE_FILES ${ALL_HEADER_FILES})

# Cache back the flags (seems to be an error of cmake for msys makefile generator)
if (NOT CFLAG_WRITE_BACK)
	SET(CFLAG_WRITE_BACK TRUE CACHE BOOL "(do not change!)" FORCE)
	mark_as_advanced(FORCE CFLAG_WRITE_BACK)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "compile flags" FORCE)
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "compile flags" FORCE)
endif ()

ADD_LIBRARY (Irrlicht ${ALL_SOURCE_FILES} )
TARGET_COMPILE_DEFINITIONS(Irrlicht PUBLIC _IRR_STATIC_LIB_)

SET_TARGET_PROPERTIES(Irrlicht PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${SOVERSION_STRING})

SET_TARGET_PROPERTIES(Irrlicht PROPERTIES COMPILE_DEFINITIONS "IRRLICHT_EXPORTS=1" )
TARGET_LINK_LIBRARIES(Irrlicht PUBLIC ${IRRLICHT_DEPENDENCY_LIBRARIES} ${OS_DEPENDENT_LIBRARIES})

INSTALL(TARGETS Irrlicht
	ARCHIVE DESTINATION  "lib" CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo
	LIBRARY DESTINATION  "lib" CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo
	RUNTIME DESTINATION  "bin" CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo
)

INSTALL(FILES ${IRRLICHT_PUBLIC_HEADER_FILES} DESTINATION "includes/Irrlicht")

if (IRRLICHT_INSTALL_MEDIA_FILES)
	INSTALL(DIRECTORY ${IRRLICHT_MEDIA_DIR} DESTINATION  ".")
endif ()

