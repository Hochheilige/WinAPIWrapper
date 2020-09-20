#include "WinAPIWrapper.h"

int main() {
	Window wnd;
	Line* line = new Line({100, 100}, {500, 500}, Style::DOT, 1, StandartColors::GREEN);
	line->Draw(wnd.GetDeviceContext());
}