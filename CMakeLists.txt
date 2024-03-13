cmake_minimum_required(VERSION 3.10)

project(PijamaCLI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files
set(SOURCES
    src/main.cpp
    # Add more source files as needed
)

# Add the YAML-CPP library (assumed to be installed or available in your project)
find_package(yaml-cpp REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${YAML_CPP_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${YAML_CPP_LIBRARIES})
