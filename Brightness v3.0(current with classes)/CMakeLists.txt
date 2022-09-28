cmake_minimum_required(VERSION 3.0.0)
project(ScreenBrightness3.0 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ScreenBrightness3.0 main.cpp MonitorBackend.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
