cmake_minimum_required (VERSION 3.3) #atleast 3.2 version or higher should be supported
project (client_socket) #project name

set(CMAKE_CXX_STANDARD 17) #atleast this much version of cpp compiler should support
SET(CMAKE_CXX_STANDARD_REQUIRED True) # if we dont have 17 or above version then dont compile


set(SOURCES
client.cpp) #add the sources file here and name it and use the name in executable.

add_executable(client_socket ${SOURCES})