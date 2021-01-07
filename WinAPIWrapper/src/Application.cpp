#include "WinAPIWrapper.h"

#include <iostream>

using namespace Waw;

int main() {
	Window wnd;
	Triangle tr({ 50, 250 }, { 650, 250 }, { 350, 150 }, StandartColors::GREEN);
	Rect rectangle({ 300, 300 }, { 400, 400 }, StandartColors::CYAN);
	tr.SetFillHatch(HatchTypes::DIAGCROSS);
	tr.SetColor(StandartColors::YELLOW);
	Circle circle({ 200, 200 }, {500, 500}, StandartColors::MAGENTA);
	circle.Draw(GetDC(wnd.GetWindow()));
	tr.Draw(GetDC(wnd.GetWindow()));
	rectangle.Draw(GetDC(wnd.GetWindow()));
	Line* line = new Line({500, 420}, {200, 420}, PenStyle::DOT, 6, StandartColors::GREEN);
	line->Draw(GetDC(wnd.GetWindow()));
} 