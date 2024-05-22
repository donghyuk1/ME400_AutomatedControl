
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Grab_and_save ${TEST_DIR}/Grab_and_save.cpp)
target_link_libraries(Grab_and_save pylon::pylon)
target_link_libraries(Grab_and_save ${OpenCV_LIBS})
