cmake_minimum_required(VERSION 3.17)
project(GameProject)

set(CMAKE_CXX_STANDARD 20)

# Define source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    headers/*.hpp
)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add executable directory
add_executable(GameProject ${SOURCES})


# Include paths
include_directories(
    headers
    C:/dev/SFML-2.5.1/include
    ${CMAKE_SOURCE_DIR}/external/tgui/include
)

# Link SFML and TGUI dynamically
target_link_directories(GameProject PUBLIC
    C:/dev/SFML-2.5.1/lib
    ${CMAKE_SOURCE_DIR}/external/tgui/lib
)

target_link_libraries(GameProject
    ${CMAKE_SOURCE_DIR}/external/tgui/bin/tgui.dll
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy assets to bin directory
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Copy DLLs for runtime
if(WIN32)
    file(GLOB SFML_DLLS "C:/dev/SFML-2.5.1/bin/*.dll")
    file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    file(GLOB TGUI_DLLS "${CMAKE_SOURCE_DIR}/external/tgui/lib/*.dll")
    file(COPY ${TGUI_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    file(GLOB MINGW_DLLS "C:/MinGW/bin/*.dll")
    file(COPY ${MINGW_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()