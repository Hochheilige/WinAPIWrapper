cmake_minimum_required(VERSION 3.15)

option(BUILD_SHARED_LIBS "Build Waw as shared library" OFF)
option(BUILD_STATIC_LIBS "Build Waw as static library" ON)
option(BUILD_EXAMPLE "Build Waw example program" ON)

if(BUILD_EXAMPLE)
    message("-- Build Waw example program")
    project(WawExample LANGUAGES CXX)
    add_executable(${PROJECT_NAME} WIN32 Application.cpp)
endif()

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PRIVATE src/)

target_link_directories(${PROJECT_NAME} PRIVATE src/)

target_link_libraries(${PROJECT_NAME} WinAPIWrapper)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
