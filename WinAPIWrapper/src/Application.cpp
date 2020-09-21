#include "WinAPIWrapper.h"
#include <conio.h>

int main() {
	Window wnd;
	Triangle tr({ 50, 200 }, { 650, 200 }, { 350, 100 }, StandartColors::GREEN);
	Rect rectangle({ 300, 300 }, { 400, 400 }, StandartColors::CYAN);
	tr.Draw(wnd.GetDeviceContext());
	tr.SetFillHatch(HatchTypes::DIAGCROSS);
	tr.SetColor(StandartColors::YELLOW);
	tr.Draw(wnd.GetDeviceContext());
	Circle circle({ 200, 200 }, {500, 500}, StandartColors::MAGENTA);
	circle.Draw(wnd.GetDeviceContext());
	rectangle.Draw(wnd.GetDeviceContext());
	//Line* line = new Line({100, 100}, {500, 500}, PenStyle::DOT, 1, StandartColors::GREEN);
	//line->Draw(wnd.GetDeviceContext());
}