cmake_minimum_required(VERSION 2.8)
set(ProjectName octo-avenger)
project(${ProjectName})
include (InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
#use git commit as patch version
find_program( Git_EXECUTABLE NAMES git git.cmd PATHS
    ${Git_DIR}
    ENV PATHS
    $ENV{Git_DIR}
)
execute_process( COMMAND ${Git_EXECUTABLE} "log" "-n" "1" "--pretty=\"%h\"" 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                 OUTPUT_VARIABLE Git_Commit_Hash 
                 OUTPUT_STRIP_TRAILING_WHITESPACE
                 )
string(REGEX REPLACE "^\"(.*)\"$" "\\1" Git_Commit_Hash ${Git_Commit_Hash} )
message(STATUS "git commit: ${Git_Commit_Hash}")
set(CPACK_PACKAGE_VERSION_PATCH ${Git_Commit_Hash})
set(CPACK_PACKAGE_VENDOR Faerbit)
include (CPack)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
if(APPLE)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
    find_package(SDL2 REQUIRED)
else()
    pkg_search_module(SDL2 REQUIRED sdl2)
endif()
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)
# SOIL Library
include_directories(${PROJECT_SOURCE_DIR}/src/soil)
file(GLOB SOIL_src ${PROJECT_SOURCE_DIR}/src/soil/*.c)
add_library(SOIL ${SOIL_src})
file(GLOB Executables ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable (${ProjectName} ${Executables})
link_directories(${PROJECT_BINARY_DIR})
target_link_libraries(${ProjectName} ${OPENGL_LIBRARIES})
target_link_libraries(${ProjectName} ${GLEW_LIBRARIES})
target_link_libraries(${ProjectName} ${SDL2_LIBRARIES})
target_link_libraries(${ProjectName} SOIL)
#copy shaders
file(COPY ${PROJECT_SOURCE_DIR}/src/shaders DESTINATION ${PROJECT_BINARY_DIR})
#copy assets
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})
#install targets
install (TARGETS ${ProjectName} DESTINATION .)
install (DIRECTORY ${PROJECT_BINARY_DIR}/shaders DESTINATION .)
install (DIRECTORY ${PROJECT_BINARY_DIR}/assets DESTINATION .)
