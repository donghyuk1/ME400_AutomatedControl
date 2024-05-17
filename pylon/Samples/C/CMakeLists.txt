# Root CMakeLists.txt for the overall Pylon project
cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0074 NEW)    # respect <PACKAGE>_ROOT variables in "find_package"
include(CMakePrintHelpers)

project(PylonSamples VERSION 0.0)
find_package(pylon 7.4.0 REQUIRED)


add_subdirectory(SimpleGrab)
add_subdirectory(Events)
add_subdirectory(ActionCommands)
add_subdirectory(OverlappedGrab)
add_subdirectory(GrabTwoCameras)
add_subdirectory(ImageDecompressor)
add_subdirectory(SurpriseRemoval)
add_subdirectory(GenApiParam)
add_subdirectory(ParametrizeCamera)
add_subdirectory(Chunks)
