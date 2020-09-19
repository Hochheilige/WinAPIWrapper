#include "Figures.h"

Line::Color::Color(StandartColors color) {
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

Pen::Pen() {
	pen = CreatePen(static_cast<int>(Style::SOLID), 1, RGB(255, 255, 255));
}

Pen::Pen(const Style st, const int32_t w, const Color clr) {
	pen = CreatePen(static_cast<int>(st), w, clr.GetColorRef());
}

void Pen::Select(const HDC hdc) {
	SelectObject(hdc, pen);
}


Triangle::Triangle() {
	vertexes[0] = {0, 0};
	vertexes[1] = {1, 0};
	vertexes[2] = {0, 1};
	line = Line();
	Line::Color tmp = Line::Color(StandartColors::WHITE);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

Triangle::Triangle(StandartColors color) {
	
	vertexes[0] = { 0, 0 };
	vertexes[1] = { 1, 0 };
	vertexes[2] = { 0, 1 };
	line = Line();
	line.SetColor(color);
	Line::Color tmp = Line::Color(color);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

Triangle::Triangle(Line::Point* const v, StandartColors color) : vertexes(v){
	line = Line();
	line.SetPoints(vertexes[0], vertexes[1]);
	line.SetColor(color);
	Line::Color tmp = Line::Color(color);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

Triangle::Triangle(const Line::Point& v1, const Line::Point& v2, const Line::Point& v3, StandartColors color) {
	vertexes[0] = v1;
	vertexes[1] = v2;
	vertexes[2] = v3;
	line = Line();
	line.SetPoints(vertexes[0], vertexes[1]);
	line.SetColor(color);
	Line::Color tmp = Line::Color(color);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

Triangle::~Triangle() {
	delete[] vertexes;
	DeleteObject(brush);
}

void Triangle::Draw(const HDC& hdc) {
	POINT points[3] = {
		{vertexes[0].x, vertexes[0].y},
		{vertexes[1].x, vertexes[1].y},
		{vertexes[2].x, vertexes[2].y},
	};
	line.Bind(hdc);
	SelectObject(hdc, brush);
	Polygon(hdc, points, 3);
}

void Triangle::SetLine(Style style, uint32_t width, StandartColors clr) {
	line.SetPen(style, width, clr);
}

void Triangle::SetLine(Style style, uint32_t width) {
	line.SetPen(style, width);
}

void Triangle::SetColor(StandartColors color) {
	line.SetColor(color);	
	Line::Color tmp = Line::Color(color);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

void Triangle::SetVertexes(Line::Point* const v) {
	vertexes = v;
}

void Triangle::SetVertexes(const Line::Point& v1, const Line::Point& v2, const Line::Point& v3) {
	vertexes[0] = v1;
	vertexes[1] = v2;
	vertexes[2] = v3;
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

