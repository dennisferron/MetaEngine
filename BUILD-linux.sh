#Linux Build Instructions

#System used:
#Ubuntu 16.04 LTS 64 bit

#All commands are in Bash and relative to the MetaEngine root folder unless otherwise specified.

#=== Install git ===

#sudo apt-get install -y git gitk git-core


#=== Install Compilers and Code::Blocks ===

sudo apt-get install -y gcc-snapshot gcc-6 g++-6
sudo apt-get install -y build-essential software-properties-common binutils
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6

# Optional: install llvm
#sudo apt-get install -y clang lldb llvm-3.8

sudo add-apt-repository ppa:damien-moore/codeblocks-stable
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install -y codeblocks codeblocks-contrib

#=== Install Irrlicht required libraries ===

sudo apt-get install -y freeglut3 freeglut3-dev freeglut3-dbg
sudo apt-get install -y xserver-xorg-dev x11proto-xf86vidmode-dev libxxf86vm-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libxext-dev libxcursor-dev

#--- Get repo
#git clone https://github.com/dennisferron/MetaEngine.git

#=== Update Submodules ===

cd MetaEngine
git submodule init
git submodule update

#=== Building Irrlicht ===

#cd Irrlict/source/Irrlicht
#make
#cd ../../..

=== Building Bullet ===

#install CMake
sudo apt-get install -y cmake-qt-gui

#The following commands did NOT work for me:
#cd bullet3
#./build_cmake_pybullet_double.sh (failed)

#Instead, I ran the CMake gui from Ubuntu's application search and used the following settings:
#Choose "Generate Unix Makefiles for default compiler"
#Click Configure
#Change/update the following settings (leave the rest default):

#Where is the source code? MetaEngine/bullet3
#Where to build the binaries? MetaEngine/bullet3/build
#EXECUTABLE_OUTPUT_PATH:PATH=/home/dennis/MetaEngine/bullet3/exe
#LIBRARY_OUTPUT_PATH:PATH=/home/dennis/MetaEngine/bullet3/lib
#USE_SOFT_BODY_MULTI_BODY_DYNAMICS_WORLD:BOOL=ON

#Important: USE_DOUBLE_PRECISION needs to be UNCHECKED (off), or else MetaEngine will get a linker error.

#Click Generate

#Then cd to the bullet3/build (not build3, build_cmake, etc) and execute "make".  I got build/#linker errors during this step, but it seems to have only affected projects which are optional.

#=== Building FLARE ===

#Install SDL2 library (note: this may also satisfy a dependency for libtcod):
sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl-ttf2.0-dev

#cd flare-engine
#cmake .
#make

#(No build errors)


#=== Building ThinPlateSpline ===

#ThinPlateSpline depends on uBLAS from boost:

sudo apt-get install -y libboost-dev

#After that, it should build fine.


#=== Building Glue ===

#If the dependencies all build, it should as well.
