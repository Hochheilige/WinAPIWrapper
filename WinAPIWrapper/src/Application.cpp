#include "WinAPIWrapper.h"

#include <iostream>

using namespace Waw;

int main() {
	Triangle tr({ 50, 250 }, { 650, 250 }, { 350, 150 }, StandartColors::GREEN);
	Rect rectangle({ 300, 300 }, { 400, 400 }, StandartColors::CYAN);
	tr.SetFillHatch(HatchTypes::DIAGCROSS);
	tr.SetColor(StandartColors::YELLOW);
	Circle circle({ 200, 200 }, {500, 500}, StandartColors::MAGENTA);
	circle.Draw();
	tr.Draw();
	rectangle.Draw();
	Line* line = new Line({500, 420}, {200, 420}, PenStyle::DOT, 6, StandartColors::GREEN);
	line->Draw();
} 