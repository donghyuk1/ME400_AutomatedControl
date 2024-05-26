
add_executable(hough_socket hough_socket.cpp)
target_link_libraries(hough_socket pylon::pylon)
target_link_libraries(hough_socket ${OpenCV_LIBS})

configure_file(${CMAKE_SOURCE_DIR}/socket/hough_read.py ${CMAKE_BINARY_DIR}/socket/hough_read.py COPYONLY)