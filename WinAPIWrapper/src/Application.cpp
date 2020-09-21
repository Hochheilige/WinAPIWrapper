#include "WinAPIWrapper.h"
#include <conio.h>

int main() {
	Window wnd;
	Triangle tr({ 50, 200 }, { 100, 250 }, { 100, 100 }, StandartColors::GREEN);
	tr.Draw(wnd.GetDeviceContext());
	Rect rectangle({ 100, 100 }, { 500, 500 }, StandartColors::CYAN);
	rectangle.Draw(wnd.GetDeviceContext());

	//Line* line = new Line({100, 100}, {500, 500}, PenStyle::DOT, 1, StandartColors::GREEN);
	//line->Draw(wnd.GetDeviceContext());

	//Brush br1(BrushStyle::SOLID, StandartColors::CYAN);
	//br1.Select(wnd.GetDeviceContext());
	//Ellipse(wnd.GetDeviceContext(), 600, 100, 900, 500);
	//Brush br2(BrushStyle::HATCH, StandartColors::MAGENTA);
	//br2.SetHatch(HatchTypes::DIAGCROSS);
	//br2.Select(wnd.GetDeviceContext());
	//Rectangle(wnd.GetDeviceContext(), 100, 100, 500, 500);
}