#!/bin/bash

echo "Make a workpiece for your C++ project"
echo ""
read -p "Enter project name: " PROJECT_NAME
echo ""

CURR_DIR=$0
CURR_DIR=$(realpath $CURR_DIR)
CURR_DIR=$(dirname $CURR_DIR)

INCLUDE=$CURR_DIR/include
SRC=$CURR_DIR/src
LIBS=$CURR_DIR/lib

if [ ! -d $INCLUDE ] || [ ! -d $SRC ] || [ ! -d $LIBS ]
then
    mkdir $INCLUDE
    mkdir $SRC
    mkdir $LIBS
fi

CMK=$CURR_DIR/'CMakeLists.txt'

echo 'cmake_minimum_required(VERSION 3.5)' > $CMK
echo "" >> $CMK
echo 'set(CMAKE_INCLUDE_CURRENT_DIR ON)' >> $CMK
echo 'set(CMAKE_CXX_STANDARD 20)' >> $CMK
echo 'set(CMAKE_CXX_STANDARD_REQUIRED ON)' >> $CMK
echo '#set(CMAKE_BUILD_TYPE Debug)' >> $CMK
echo "" >> $CMK
echo 'set(CMAKE_BINARY_DIR app)' >> $CMK
echo 'set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)' >> $CMK
echo 'set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/shared)' >> $CMK
echo 'set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)' >> $CMK
echo "" >> $CMK
echo 'project('$PROJECT_NAME' LANGUAGES CXX)' >> $CMK
echo "" >> $CMK
echo 'set(SRC src/main.cpp)' >> $CMK
echo "" >> $CMK
echo '#add_library(one STATIC lib/*.h lib/*.cpp)' >> $CMK
echo '#add_library(two SHARED lib/*.h lib/*.cpp)' >> $CMK
echo "" >> $CMK
echo 'add_executable(${CMAKE_PROJECT_NAME} ${SRC})' >> $CMK
echo '#target_link_libraries(${CMAKE_PROJECT_NAME} one)' >> $CMK
echo '#target_link_libraries(${CMAKE_PROJECT_NAME} two)' >> $CMK

C_FILE=$SRC/main.cpp

echo '#include <iostream>' > $C_FILE
echo "" >> $C_FILE
echo 'int main()' >> $C_FILE
echo '{' >> $C_FILE
echo '  std::cout << "Project name: '$PROJECT_NAME'" << std::endl;' >> $C_FILE
echo '	return 0;' >> $C_FILE
echo '}' >> $C_FILE

BUILD=$CURR_DIR/'build.sh'

echo '#!/bin/bash' > $BUILD
echo "" >> $BUILD
echo 'CURR_DIR=$0' >> $BUILD
echo 'CURR_DIR=$(realpath $CURR_DIR)' >> $BUILD
echo 'CURR_DIR=$(dirname $CURR_DIR)' >> $BUILD
echo "" >> $BUILD
echo 'BUILD_TARGET=$CURR_DIR/build' >> $BUILD
echo "" >> $BUILD
echo '#rm -rd $BUILD_TARGET' >> $BUILD
echo "" >> $BUILD
echo 'if [ -d $BUILD_TARGET ]' >> $BUILD
echo 'then' >> $BUILD
echo '  cd $BUILD_TARGET' >> $BUILD
echo 'else' >> $BUILD
echo '  mkdir $BUILD_TARGET' >> $BUILD
echo '  cd $BUILD_TARGET' >> $BUILD
echo 'fi' >> $BUILD
echo "" >> $BUILD
echo 'cmake -B $BUILD_TARGET -S $CURR_DIR' >> $BUILD
echo 'cmake --build .' >> $BUILD
echo "" >> $BUILD
echo 'exec $SHELL' >> $BUILD

chmod u+x $BUILD

RUN=$CURR_DIR/run.sh

echo '#!/bin/bash' > $RUN
echo "" >> $RUN
echo './build/app/bin/'$PROJECT_NAME >> $RUN
echo "" >> $RUN
echo 'exec $SHELL' >> $RUN

chmod u+x $RUN

chmod -x start.sh
ls

exec $SHELL
