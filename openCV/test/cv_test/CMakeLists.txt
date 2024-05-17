find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable( cv_test cv_test.cpp)
add_executable( hough_test hough_test.cpp)


target_link_libraries( cv_test PRIVATE ${OpenCV_LIBS})
target_link_libraries( hough_test ${OpenCV_LIBS})

install( TARGETS cv_test hough_test)