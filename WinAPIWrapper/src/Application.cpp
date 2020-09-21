#include "WinAPIWrapper.h"

int main() {
	Window wnd;

	Pen p;
	p.Select(wnd.GetDeviceContext());
	MoveToEx(wnd.GetDeviceContext(), 100, 100, nullptr);
	LineTo(wnd.GetDeviceContext(), 500, 300);

	Line* line = new Line({100, 100}, {500, 500}, PenStyle::DOT, 1, StandartColors::GREEN);
	line->Draw(wnd.GetDeviceContext());

	Brush br1(BrushStyle::SOLID, StandartColors::CYAN);
	br1.Select(wnd.GetDeviceContext());
	Ellipse(wnd.GetDeviceContext(), 600, 100, 900, 500);
	Brush br2(BrushStyle::HATCH, StandartColors::MAGENTA);
	br2.SetHatch(HatchTypes::DIAGCROSS);
	br2.Select(wnd.GetDeviceContext());
	Rectangle(wnd.GetDeviceContext(), 100, 100, 500, 500);
	
	Triangle tr;
	tr.Draw(wnd.GetDeviceContext());
}