#include "Figures.h"

Color::Color(StandartColors color) {
	switch (color) {
		case StandartColors::WHITE: {
			red = green = blue = 255;
			break;
		}
		case StandartColors::BLACK: {
			red = green = blue = 0;
			break;
		}
		case StandartColors::RED: {
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

Pen::Pen() : style(PenStyle::SOLID), width(1), color(Color()) {
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

Pen::Pen(const PenStyle st, const int32_t w, const Color clr)
	: style(st), width(w), color(clr) {
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

Pen::Pen(const PenStyle st, const int32_t w, const StandartColors clr)
	: style(st), width(w), color(clr) {
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

void Pen::SetStyle(const PenStyle st) {
	style = st;
	DeleteObject(pen);
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

void Pen::SetWidth(const int32_t w) {
	width = w;
	DeleteObject(pen);
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

void Pen::SetColor(const Color clr) {
	color = clr;
	DeleteObject(pen);
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

void Pen::SetColor(const StandartColors clr) {
	color = Color(clr);
	DeleteObject(pen);
	pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
}

void Pen::Select(const HDC hdc) {
	SelectObject(hdc, pen);
}

Brush::Brush() {
	style = BrushStyle::SOLID;
	color = Color();
	hatch = HatchTypes::HORIZONTAL;
	bitmap = nullptr;
	brush = CreateSolidBrush(color.GetColorRef());
}

Brush::Brush(const BrushStyle st, const Color clr, 
			 const HatchTypes hatch_type, HBITMAP bm) {
	style = st;
	color = clr;
	hatch = hatch_type;
	bitmap = bm;
	SelectStyle();
}

Brush::Brush(const BrushStyle st, const StandartColors clr,
			 const HatchTypes hatch_type, HBITMAP bm) {
	style = st;
	color = Color(clr);
	hatch = hatch_type;
	bitmap = bm;
	SelectStyle();
}

void Brush::SetBrushStyle(const BrushStyle st, const HatchTypes hatch_type, HBITMAP bm) {
	style = st;
	hatch = hatch_type;
	bitmap = bm;
	DeleteObject(brush);
	SelectStyle();
}

void Brush::SetHatch(HatchTypes hatch_type) {
	hatch = hatch_type;
	DeleteObject(brush);
	SelectStyle();
}

void Brush::SetColor(const Color clr) {
	color = clr;
	DeleteObject(brush);
	SelectStyle();
}

void Brush::SetColor(const StandartColors clr) {
	color = Color(clr);
	DeleteObject(brush);
	SelectStyle();
}

void Brush::SetBitmap(const HBITMAP bm) {
	bitmap = bm;
	DeleteObject(brush);
	SelectStyle();
}

void Brush::Select(const HDC hdc) {
	if (brush)
		SelectObject(hdc, brush);
}

void Brush::SelectStyle() {
	switch (style) {
		case BrushStyle::SOLID: {
			brush = CreateSolidBrush(color.GetColorRef());
			break;
		}
		case BrushStyle::HATCH: {
			brush = CreateHatchBrush(static_cast<int>(hatch), color.GetColorRef());
			break;
		}
		case BrushStyle::PATTERN: {
			brush = CreatePatternBrush(bitmap);
			break;
		}
	}
}

Line::Line() {
	entry = new Point(0, 0);
	destination = new Point(1, 1);
	pen = new Pen(PenStyle::SOLID, 1, Color(StandartColors::WHITE));
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

Line::Line(const Point start, const Point finish, PenStyle style, int32_t width, StandartColors color) {
	entry = new Point(start);
	destination = new Point(finish);
	pen = new Pen(style, width, color);
}

Line::Line(Point* start, Point* finish, PenStyle style, int32_t width, StandartColors color) {
	entry = start;
	destination = finish;
	pen = new Pen(style, width, color);
}

Line::Line(Point* points[], PenStyle style, int32_t width, StandartColors color) {
	entry = points[0];
	destination = points[1];
	pen = new Pen(style, width, color);
}

void Line::Draw(const HDC hdc) {
	pen->Select(hdc);
	MoveToEx(hdc, entry->x, entry->y, nullptr);
	LineTo(hdc, destination->x, destination->y);
}

Triangle::Triangle() {
	vertexes = new Point[3]{ {100, 0}, {100, 100}, {0, 100} };
	pen = new Pen();
	brush = new Brush();
}

void Triangle::Draw(const HDC hdc) {
	pen->Select(hdc);
	brush->Select(hdc);
	POINT* points = new POINT[3]{
		{vertexes[0].x, vertexes[0].y},
		{vertexes[1].x, vertexes[1].y},
		{vertexes[2].x, vertexes[2].x}
	};
	Polygon(hdc, points, 3);
}
