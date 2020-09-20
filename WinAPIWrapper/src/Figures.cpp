#include "Figures.h"

Color::Color(StandartColors color) {
	switch (color) {
		case StandartColors::WHITE:
		{
			red = green = blue = 255;
			break;
		}
		case StandartColors::BLACK:
		{
			red = green = blue = 0;
			break;
		}
		case StandartColors::RED:
		{
			red = 255;
			green = blue = 0;
			break;
		}
		case StandartColors::GREEN: {
			green = 255;
			red = blue = 0;
			break;
		}
		case StandartColors::BLUE: {
			blue = 255;
			red = green = 0;
			break;
		}
		case StandartColors::YELLOW: {
			red = green = 255;
			blue = 0;
			break;
		}
		case StandartColors::CYAN: {
			green = blue = 255;
			red = 0;
			break;
		}
		case StandartColors::MAGENTA: {
			red = blue = 255;
			green = 0;
			break;
		}
		default: {
			red = green = blue = 0;
			break;
		}	
	}
}

COLORREF Color::GetColorRef() const {
	return RGB(red, green, blue);
}

Pen::Pen() : style(Style::SOLID), width(1), color(Color()) {
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

Pen::Pen(const Style st, const int32_t w, const Color clr)
	: style(st), width(w), color(clr) {
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

Pen::Pen(const Style st, const int32_t w, const StandartColors clr) 
	: style(st), width(w), color(clr) {
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

void Pen::Select(const HDC hdc) {
	SelectObject(hdc, pen);
}

Line::Line() {
	entry = new Point(0, 0);
	destination = new Point(1, 1);
	pen = new Pen(Style::SOLID, 1, Color(StandartColors::WHITE));
}

Line::Line(const Point start, const Point finish, Pen pn) {
	entry = new Point(start);
	destination = new Point(finish);
	pen = new Pen(pn);
}

Line::Line(Point* start, Point* finish, Pen* pn) {
	entry = start;
	destination = finish;
	pen = pn;
}

Line::Line(Point* points[], Pen* pn) {
	entry = points[0];
	destination = points[1];
	pen = pn;
}

Line::Line(const Point start, const Point finish, Style style, int32_t width, StandartColors color) {
	entry = new Point(start);
	destination = new Point(finish);
	pen = new Pen(style, width, color);
}

Line::Line(Point* start, Point* finish, Style style, int32_t width, StandartColors color) {
	entry = start;
	destination = finish;
	pen = new Pen(style, width, color);
}

Line::Line(Point* points[], Style style, int32_t width, StandartColors color) {
	entry = points[0];
	destination = points[1];
	pen = new Pen(style, width, color);
}

void Line::Draw(const HDC hdc) {
	pen->Select(hdc);
	MoveToEx(hdc, entry->x, entry->y, nullptr);
	LineTo(hdc, destination->x, destination->y);
}

