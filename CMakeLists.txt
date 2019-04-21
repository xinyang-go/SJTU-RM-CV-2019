cmake_minimum_required(VERSION 3.5)

project(auto-aim)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE DEBUG)

FIND_PROGRAM(CCACHE_FOUND ccache)
IF(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    message("< Use ccache for compiler >")
ENDIF()

FIND_PACKAGE(OpenCV 3 REQUIRED)
FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(Threads)

include_directories( ${EIGEN3_INCLUDE_DIR} )
include_directories( ${PROJECT_SOURCE_DIR}/energy/include )
include_directories( ${PROJECT_SOURCE_DIR}/armor/include )
include_directories( ${PROJECT_SOURCE_DIR}/include )

FILE(GLOB_RECURSE sourcefiles "src/*.cpp" "energy/src/*cpp" "armor/src/*.cpp")
add_executable(run main.cpp ${sourcefiles} )

TARGET_LINK_LIBRARIES(run ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES(run ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(run ${PROJECT_SOURCE_DIR}/libMVSDK.so)
