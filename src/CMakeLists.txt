list(
APPEND
    WawSrc 
	Brush.cpp
        Brush.h
	Circle.cpp
        Circle.h
	Color.cpp
        Color.h
	Line.cpp
        Line.h
	Pen.cpp
        Pen.h
	Point.cpp
        Point.h
	Rect.cpp
        Rect.h
	Triangle.cpp
        Triangle.h
	Window.cpp
        Window.h
        Figures.h
        Styles.h
        Resource.h
)

if(BUILD_EXAMPLE)
    message("-- Build WinAPIWrapper as static library")
    add_library(WinAPIWrapper STATIC ${WawSrc} ../include/WinAPIWrapper.h)
else()
    if(BUILD_AS_SHARED_LIB)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
        message("-- Build WinAPIWrapper as shared library")
        add_library(WinAPIWrapper SHARED ${WawSrc})
	
		add_custom_command(TARGET WinAPIWrapper POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different 
				"${CMAKE_BINARY_DIR}/src/$<CONFIGURATION>/WinAPIWrapper.lib"
				 ${CMAKE_SOURCE_DIR}/include/
		)

		add_custom_command(TARGET WinAPIWrapper POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different 
				"${CMAKE_BINARY_DIR}/src/$<CONFIGURATION>/WinAPIWrapper.dll"
				 ${CMAKE_SOURCE_DIR}/include/
		)

    elseif(BUILD_AS_STATIC_LIB)
        message("-- Build WinAPIWrapper as static library")
        add_library(WinAPIWrapper STATIC ${WawSrc})

		add_custom_command(TARGET WinAPIWrapper POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different 
				"${CMAKE_BINARY_DIR}/src/$<CONFIGURATION>/WinAPIWrapper.lib"
				 ${CMAKE_SOURCE_DIR}/include/
		)
	else()
		message("-- Warning you didn't choose WinAPIWrapper build option")
    endif()

	target_include_directories(WinAPIWrapper
    	PRIVATE ${CMAKE_SOURCE_DIR}/src/
    	PRIVATE ${CMAKE_SOURCE_DIR}/include/
	)

	target_link_directories(WinAPIWrapper 
    	PRIVATE ${CMAKE_SOURCE_DIR}/src/
    	PRIVATE ${CMAKE_SOURCE_DIR}/include/
	)
endif() 

target_compile_features(WinAPIWrapper PRIVATE cxx_std_17)