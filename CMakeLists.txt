cmake_minimum_required(VERSION 2.8)
set(ProjectName mustached-octo-avenger)
project(${ProjectName})
include (InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE
    "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include (CPack)
add_subdirectory(src)
