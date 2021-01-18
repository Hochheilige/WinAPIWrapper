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
        WinAPIWrapper.h
        Figures.h
        Styles.h
)

if(BUILD_EXAMPLE)
    if(BUILD_SHARED_LIBS)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
        message("-- Build WinAPIWrapper as shared library")
        add_library(WinAPIWrapper SHARED ${WawSrc})
    elseif(BUILD_STATIC_LIBS)
        message("-- Build WinAPIWrapper as static library")
        add_library(WinAPIWrapper STATIC ${WawSrc})
    endif()
endif() 

target_compile_features(WinAPIWrapper PRIVATE cxx_std_17)