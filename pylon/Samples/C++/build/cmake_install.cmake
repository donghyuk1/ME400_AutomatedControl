# Install script for directory: /home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/DeviceRemovalHandling/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_CameraEvents/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_UsingBufferFactory/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_MultipleCameras/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_UsingExposureEndEvent/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_UsingSequencer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_MultiCast/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_UsingGrabLoopThread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_UsingActionCommand/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_ChunkImage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Utility_GrabVideo/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Utility_FFC/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Grab_Strategies/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_NativeParameterAccess/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_Shading/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_UserSets/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_AutoFunctions/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_SerialCommunication/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_LookupTable/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_LoadAndSave/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_GenericParameterAccess/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/ParametrizeCamera_Configurations/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Utility_ImageDecompressor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Utility_InstantInterface/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Utility_ImageLoadAndSave/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Utility_ImageFormatConverter/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/Utility_IpConfig/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/donghyuk/workspace/ME400/AutomatedControl/pylon/Samples/C++/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
