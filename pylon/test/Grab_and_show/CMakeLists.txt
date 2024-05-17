# Root CMakeLists.txt for the overall Pylon project
cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0074 NEW)    # respect <PACKAGE>_ROOT variables in "find_package"
include(CMakePrintHelpers)



project(PylonSamples VERSION 0.0)
find_package(pylon 7.4.0 REQUIRED)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable( Grab_and_show Grab_and_show.cpp)
target_link_libraries( Grab_and_show PRIVATE pylon::pylon )
target_link_libraries( Grab_and_show PRIVATE ${OpenCV_LIBS})

target_link_libraries(openCVGrab pylon::pylon)
target_link_libraries(openCVGrab ${OpenCV_LIBS})

install( TARGETS Grab_and_show openCVGrab)

