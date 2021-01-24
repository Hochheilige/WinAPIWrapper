# WinAPIWrapper
Simple OOP Wrapper under WinAPI to draw simple figures like Triangles, Rectangles and Circles.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

To generate, build and run this project you should have CMake installed and use compiler that supports C++17

### Example

To run the example you just can sequentially run files in CMakeBuilds directory:

1. configure.bat - to generate configuretion to the project
2. build.bat - to build the project
3. run.bat - to run the project

Another way - using simple CMake commands:

```
cmake -S .. -B ../out/build/
cmake --build ../out/build
cd ../out/build/Debug
WawExample.exe
```

If all this actions completed successfully you will see example image

![WinAPIWrapper](/Resources/example.PNG?raw=true "Example Image")

## Using as library

### Configure and build

You can use WinAPIWrapper as static or shared library. This can be selected using CMake options:

* Static library
```
cmake -S .. -B ../out/build/ -DBUILD_EXAMPLE=OFF
cmake --build ../out/build 
```

* Shared library
```
cmake -S .. -B ../out/build/ -DBUILD_EXAMPLE=OFF -DBUILD_SHARED_LIBS=ON
cmake --build ../out/build
```

### Run

After that in your application you should include WinAPIWrapper.h and create HINSTANCE, WndProc function decalration and classical WinAPI main function.

```
#include <WinAPIWrapper.h>

HINSTANCE hInst; 

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	hInst = hInstance;
	Waw::Window window(hInst, nCmdShow, WndProc);

	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_WAW));
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
```

* To create a window use Window class from Waw namespace:
```
Waw::Window window(hInst, nCmdShow, WndProc);
```
* You can set window dimensions like this:
```
Waw::Window window(hInst, nCmdShow, WndProc, 800, 600);
```

The last step to get started is to create a WndProc function definition:
```
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_COMMAND: {
			int wmId = LOWORD(wParam);
			switch (wmId) {
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, NULL);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		} break;
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			Triangle tr({ 90, 250 }, { 390, 150 }, { 690, 250 }, StandartColors::GREEN);
            tr.Draw(hdc);

			EndPaint(hWnd, &ps);
		} break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
```

You can create all objects in this function and Draw it in WM_PAINT case. In this example you will see green trinangle.

## Authors

* **Pavel Ovchinnikov** - [Hochheilige](https://github.com/Hochheilige)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
