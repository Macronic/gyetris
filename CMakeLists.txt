
project(gyetris)
cmake_minimum_required(VERSION 2.8)

add_compile_definitions(VERSION="2.3.0")
add_compile_definitions(DATE="2019.03.16")
#TO DO: unhardcode date
add_compile_definitions(PACKAGE="${PROJECT_NAME}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -O0 ")
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules/"  "/usr/share/SFML/cmake/Modules/")
endif()

set(HEADERS
   ${HEADERS}
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/" "${CMAKE_CURRENT_SOURCE_DIR}/deps" "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCES "src/Main.cpp" "deps/Engine/*.cpp" "deps/commander/*.c" "src/Game/Config/*.cpp" "src/Game/Display/*.cpp" "src/Game/Display/Layouts/*.cpp" "src/Game/Entities/*.cpp" "src/Game/States/*.cpp" )

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(SFML 2 REQUIRED system window graphics network audio)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_package(SFML 2 REQUIRED main system window graphics network audio)
endif() #

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ncurses)
