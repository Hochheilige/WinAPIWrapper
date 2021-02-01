cmake_minimum_required(VERSION 3.15)

option(BUILD_AS_SHARED_LIB "Build Waw as shared library" OFF)
option(BUILD_AS_STATIC_LIB "Build Waw as static library" OFF)
option(BUILD_EXAMPLE "Build Waw example program" OFF)

if(BUILD_EXAMPLE)
    message("-- Build Waw example program")
    project(WawExample LANGUAGES CXX)

    add_subdirectory(examples)
  
    add_subdirectory(src)

    target_include_directories(${PROJECT_NAME}
	    PRIVATE src/
	    PRIVATE include/  
    )

    target_link_directories(${PROJECT_NAME} 
	    PRIVATE src/
	    PRIVATE include/
    )

    target_link_libraries(${PROJECT_NAME} WinAPIWrapper)

    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
else()
    project(Wawlib LANGUAGES CXX)
    add_subdirectory(src)
endif()

