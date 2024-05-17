# Root CMakeLists.txt for the overall Pylon project
cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0074 NEW)    # respect <PACKAGE>_ROOT variables in "find_package"
include(CMakePrintHelpers)



project(PylonSamples VERSION 0.0)
find_package(pylon 7.4.0 REQUIRED)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable( realtime_hough realtime_hough.cpp)

target_link_libraries(realtime_hough pylon::pylon)
target_link_libraries(realtime_hough ${OpenCV_LIBS})

install( TARGETS realtime_hough)

