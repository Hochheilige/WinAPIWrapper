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
)

if(BUILD_EXAMPLE)
    message("-- Build WinAPIWrapper as static library")
    add_library(WinAPIWrapper STATIC ${WawSrc} ../include/WinAPIWrapper.h)
else()
    if(BUILD_AS_SHARED_LIB)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
        message("-- Build WinAPIWrapper as shared library")
        add_library(WinAPIWrapper SHARED ${WawSrc} ../include/WinAPIWrapper.h)
    elseif(BUILD_AS_STATIC_LIB)
        message("-- Build WinAPIWrapper as static library")
        add_library(WinAPIWrapper STATIC ${WawSrc} ../include/WinAPIWrapper.h)
    else()
	message("-- Warning you didn't choose WinAPIWrapper build option")
    endif()

endif() 

	target_include_directories(WinAPIWrapper
    	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	)

	target_link_directories(WinAPIWrapper 
    	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	)

target_compile_features(WinAPIWrapper PRIVATE cxx_std_17)