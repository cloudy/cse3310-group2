// Run the following commands to setup Doxygen:

git clone https://github.com/doxygen/doxygen.git

cd doxygen

mkdir build

cd build

cmake -G "Unix Makefiles" ..

// Might have to install some packages (flex, qt-sdk)

cmake -Dbuild_wizard=YES ..

make

make install