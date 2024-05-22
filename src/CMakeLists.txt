# Root CMakeLists.txt for the overall Pylon project
cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0074 NEW)    # respect <PACKAGE>_ROOT variables in "find_package"
include(CMakePrintHelpers)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})


project(AutomatedControl VERSION 0.0)
find_package(pylon 7.4.0 REQUIRED)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(test)

add_executable( realtime_hough ${SRC_DIR}/realtime_hough.cpp)
target_link_libraries(realtime_hough pylon::pylon)
target_link_libraries(realtime_hough ${OpenCV_LIBS})

add_executable( realtime_hough_undistorted ${SRC_DIR}/realtime_hough_undistort.cpp)
target_link_libraries(realtime_hough_undistorted pylon::pylon)
target_link_libraries(realtime_hough_undistorted ${OpenCV_LIBS})

add_executable( realtime_edge ${SRC_DIR}/realtime_edge.cpp)
target_link_libraries(realtime_edge pylon::pylon)
target_link_libraries(realtime_edge ${OpenCV_LIBS})

install( TARGETS realtime_hough_undistorted)

