#pragma once

#include <cstdint>
#include <cmath>

#include <Windows.h>

class Window {
public:
	Window();
	~Window();

	inline HANDLE GetHandle() { return hStdout; }
	inline CONSOLE_SCREEN_BUFFER_INFO GetScreenBufferInfo() { return csbi; }
	inline HWND GetWindow() { return hWindow; }
	inline HDC GetDeviceContext() { return hDeviceContext; }
private:
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND hWindow;
	HDC hDeviceContext;
};

Window::Window() {
	GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &csbi);
	hWindow = GetConsoleWindow();
	hDeviceContext = GetDC(hWindow);
}

Window::~Window() {
	ReleaseDC(hWindow, hDeviceContext);
}

enum class PenStyle {
	SOLID,
	DASH,
	DOT,
	DASHDOT,
	DASHDOTDOT,
	INVISIBLE,
	INSIDEFRAME
};

enum class BrushStyle {
	SOLID,
	HATCH,
	PATTERN
};

enum class HatchTypes {
	HORIZONTAL,
	VERTICAL,
	FDIAGONAL, // from left top to right bottom
	BDIAGONAL, // from left bottom to right top
	CROSS,
	DIAGCROSS,
};

enum class StandartColors {
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	CYAN,
	MAGENTA
};

struct Point {
	int32_t x, y;

	Point() : x(0), y(0) {}
	Point(const int32_t x_coord, const int32_t y_coord)
		: x(x_coord), y(y_coord) {
	}
	Point(const Point& point) : x(point.x), y(point.y) {}
};

struct Color {
	uint16_t red, green, blue;

	Color() : red(255), green(255), blue(255) {}
	Color(const uint16_t r, const uint16_t g, const uint16_t b) : red(r), green(g), blue(b) {}
	explicit Color(const StandartColors color);

	COLORREF GetColorRef() const;
};

class Pen {
public:
	Pen();
	Pen(const PenStyle st, const int32_t w, const Color clr);
	Pen(const PenStyle st, const int32_t w, const StandartColors clr);

	void SetStyle(const PenStyle st);
	void SetWidth(const int32_t w);
	void SetColor(const Color clr);
	void SetColor(const StandartColors clr);
	void Select(const HDC hdc);
private:
	HPEN pen;
	PenStyle style;
	int32_t width;
	Color color;
};

class Brush {
public:
	Brush();
	Brush(const BrushStyle st, const Color clr,
		  const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		  const HBITMAP bm = nullptr);
	Brush(const BrushStyle st, const StandartColors clr,
		  const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		  const HBITMAP bm = nullptr);

	void SetBrushStyle(const BrushStyle st,
					   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
					   const HBITMAP bm = nullptr);
	void SetHatch(const HatchTypes hatch_type);
	void SetColor(const Color clr);
	void SetColor(const StandartColors clr);
	void SetBitmap(const HBITMAP bm);
	void Select(const HDC hdc);
private:
	HBRUSH brush;
	BrushStyle style;
	Color color;
	HatchTypes hatch;
	HBITMAP bitmap;

	void SelectStyle();
};

class Line {
public:
	Line();
	Line(const Point start, const Point finish, const Pen pn = Pen());
	Line(Point* start, Point* finish, Pen* pn = new Pen());
	Line(Point* points[], Pen* pn = new Pen());
	Line(const Point start, const Point finish, const PenStyle style = PenStyle::SOLID,
		 const int32_t width = 1, const StandartColors color = StandartColors::WHITE);
	Line(Point* start, Point* finish, const PenStyle style = PenStyle::SOLID,
		 const int32_t width = 1, const StandartColors color = StandartColors::WHITE);
	Line(Point* points[], const PenStyle style = PenStyle::SOLID,
		 const int32_t width = 1, const StandartColors color = StandartColors::WHITE);

	void Draw(const HDC hdc) const;
	void SetCoord(const Point start, const Point finish);
	inline void SetEntry(const Point start) { *entry = start; }
	inline void SetDestination(const Point finish) { *destination = finish; }
	inline void SetColor(const Color color) { pen->SetColor(color); }
	inline void SetColor(const StandartColors color) { pen->SetColor(color); }
	inline void SetStyle(const PenStyle style) { pen->SetStyle(style); }
	inline void SetWidth(const int32_t width) { pen->SetWidth(width); }
	inline int32_t GetLength() {
		return sqrt(
			pow((destination->x - entry->x), 2) +
			pow((destination->y - entry->y), 2)
		);
	}
	inline Point GetEntry() { return { entry->x, entry->y }; }
	inline Point GetDestination() { return { destination->x, destination->y }; }
private:
	Point* entry = nullptr, * destination = nullptr;
	Pen* pen = nullptr;
};

class Figure {
public:
	virtual void Draw(const HDC hdc) = 0;
	virtual void SetColor(const Color color) = 0;
	virtual void SetColor(const StandartColors color) = 0;
	inline void SetContourColor(const Color color) { pen->SetColor(color); }
	inline void SetContourColor(const StandartColors color) { pen->SetColor(color); }
	inline void SetContourStyle(const PenStyle style) { pen->SetStyle(style); }
	inline void SetContourWidth(const int32_t width) { pen->SetWidth(width); }
	inline void SetFillColor(const Color color) { brush->SetColor(color); }
	inline void SetFillColor(const StandartColors color) { brush->SetColor(color); }
	inline void SetFillStyle(const BrushStyle style,
							 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
							 const HBITMAP bm = nullptr) {
		brush->SetBrushStyle(style);
	}
	inline void SetFillHatch(const HatchTypes hatch_type) { brush->SetBrushStyle(BrushStyle::HATCH, hatch_type); }
protected:
	Point* vertexes = nullptr;
	Pen* pen = nullptr;
	Brush* brush = nullptr;
};

class Triangle : public Figure {
public:
	Triangle();
	Triangle(const Point v1, const Point v2, const Point v3,
			 const Color inner = Color(), const Color contour = Color(),
			 const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
			 const BrushStyle brush_style = BrushStyle::SOLID,
			 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
			 const HBITMAP bm = nullptr);
	Triangle(const Point v1, const Point v2, const Point v3,
			 const StandartColors inner = StandartColors::WHITE,
			 const StandartColors contour = StandartColors::WHITE,
			 const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
			 const BrushStyle brush_style = BrushStyle::SOLID,
			 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
			 const HBITMAP bm = nullptr);
	~Triangle();
	void Draw(const HDC hdc) override;
	void SetColor(const Color color) override;
	void SetColor(const StandartColors color) override;
	void SetVertexes(const Point v1, const Point v2, const Point v3);
};

class Rect : public Figure {
public:
	Rect();
	Rect(const Point left_top, const Point right_bottom,
		 const Color inner = Color(), const Color contour = Color(),
		 const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
		 const BrushStyle brush_style = BrushStyle::SOLID,
		 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		 const HBITMAP bm = nullptr);
	Rect(const Point left_top, const Point right_bottom,
		 const StandartColors inner = StandartColors::WHITE,
		 const StandartColors contour = StandartColors::WHITE,
		 const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
		 const BrushStyle brush_style = BrushStyle::SOLID,
		 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		 const HBITMAP bm = nullptr);
	~Rect();
	void Draw(const HDC hdc) override;
	void SetColor(const Color color) override;
	void SetColor(const StandartColors color) override;
	void SetVertexes(const Point left_top, const Point right_bottom);
};

class Circle : public Figure {
public:
	Circle();
	Circle(const Point left_top, const Point right_bottom,
		   const Color inner = Color(), const Color contour = Color(),
		   const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
		   const BrushStyle brush_style = BrushStyle::SOLID,
		   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		   const HBITMAP bm = nullptr);
	Circle(const Point left_top, const Point right_bottom,
		   const StandartColors inner = StandartColors::WHITE,
		   const StandartColors contour = StandartColors::WHITE,
		   const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
		   const BrushStyle brush_style = BrushStyle::SOLID,
		   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		   const HBITMAP bm = nullptr);
	~Circle();
	void Draw(const HDC hdc) override;
	void SetColor(const Color color) override;
	void SetColor(const StandartColors color) override;
	void SetVertexes(const Point left_top, const Point right_bottom);
};

Color::Color(const StandartColors color) {
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
		case StandartColors::GREEN:
		{
			green = 255;
			red = blue = 0;
			break;
		}
		case StandartColors::BLUE:
		{
			blue = 255;
			red = green = 0;
			break;
		}
		case StandartColors::YELLOW:
		{
			red = green = 255;
			blue = 0;
			break;
		}
		case StandartColors::CYAN:
		{
			green = blue = 255;
			red = 0;
			break;
		}
		case StandartColors::MAGENTA:
		{
			red = blue = 255;
			green = 0;
			break;
		}
		default:
		{
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
	if (pen)
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
			 const HatchTypes hatch_type, const HBITMAP bm) {
	style = st;
	color = clr;
	hatch = hatch_type;
	bitmap = bm;
	SelectStyle();
}

Brush::Brush(const BrushStyle st, const StandartColors clr,
			 const HatchTypes hatch_type, const HBITMAP bm) {
	style = st;
	color = Color(clr);
	hatch = hatch_type;
	bitmap = bm;
	SelectStyle();
}

void Brush::SetBrushStyle(const BrushStyle st, const HatchTypes hatch_type,
						  const HBITMAP bm) {
	style = st;
	hatch = hatch_type;
	bitmap = bm;
	DeleteObject(brush);
	SelectStyle();
}

void Brush::SetHatch(const HatchTypes hatch_type) {
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
		case BrushStyle::SOLID:
		{
			brush = CreateSolidBrush(color.GetColorRef());
			break;
		}
		case BrushStyle::HATCH:
		{
			brush = CreateHatchBrush(static_cast<int>(hatch), color.GetColorRef());
			break;
		}
		case BrushStyle::PATTERN:
		{
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

Line::Line(Point* start, Point* finish, const PenStyle style,
		   const int32_t width, const StandartColors color) {
	entry = start;
	destination = finish;
	pen = new Pen(style, width, color);
}

Line::Line(Point* points[], const PenStyle style,
		   const int32_t width, const StandartColors color) {
	entry = points[0];
	destination = points[1];
	pen = new Pen(style, width, color);
}

void Line::Draw(const HDC hdc) const {
	pen->Select(hdc);
	MoveToEx(hdc, entry->x, entry->y, nullptr);
	LineTo(hdc, destination->x, destination->y);
}

void Line::SetCoord(const Point start, const Point finish) {
	*entry = start;
	*destination = finish;
}

Triangle::Triangle() {
	vertexes = new Point[3]{
		{ 100, 0   },
		{ 0  , 100 },
		{ 100, 100 }
	};
	pen = new Pen();
	brush = new Brush();
}

Triangle::Triangle(const Point v1, const Point v2, const Point v3,
				   const Color inner, const Color contour,
				   const PenStyle pen_style, const int32_t width,
				   const BrushStyle brush_style, const HatchTypes hatch_type,
				   const HBITMAP bm) {
	vertexes = new Point[3]{ v1, v2, v3 };
	pen = new Pen(pen_style, width, contour);
	brush = new Brush(brush_style, inner, hatch_type, bm);
}

Triangle::Triangle(const Point v1, const Point v2, const Point v3,
				   const StandartColors inner, const StandartColors contour,
				   const PenStyle pen_style, const int32_t width,
				   const BrushStyle brush_style, const HatchTypes hatch_type,
				   const HBITMAP bm) {
	vertexes = new Point[3]{ v1, v2, v3 };
	pen = new Pen(pen_style, width, contour);
	brush = new Brush(brush_style, inner, hatch_type, bm);
}

Triangle::~Triangle() {
	delete[] vertexes;
	delete pen;
	delete brush;
}

void Triangle::Draw(const HDC hdc) {
	pen->Select(hdc);
	brush->Select(hdc);
	POINT* points = new POINT[3]{
		{ vertexes[0].x, vertexes[0].y },
		{ vertexes[1].x, vertexes[1].y },
		{ vertexes[2].x, vertexes[2].x }
	};
	Polygon(hdc, points, 3);
}

void Triangle::SetVertexes(const Point v1, const Point v2, const Point v3) {
	vertexes[0] = v1;
	vertexes[1] = v2;
	vertexes[2] = v3;
}

void Triangle::SetColor(const Color color) {
	pen->SetColor(color);
	brush->SetColor(color);
}

void Triangle::SetColor(const StandartColors color) {
	pen->SetColor(color);
	brush->SetColor(color);
}

Rect::Rect() {
	vertexes = new Point[2]{
		{0, 0},
		{100, 100}
	};
	pen = new Pen();
	brush = new Brush();
}

Rect::Rect(const Point left_top, const Point right_bottom,
		   const Color inner, const Color contour,
		   const PenStyle pen_style, const int32_t width,
		   const BrushStyle brush_style, const HatchTypes hatch_type,
		   const HBITMAP bm) {
	vertexes = new Point[2]{
		left_top,
		right_bottom
	};
	pen = new Pen(pen_style, width, contour);
	brush = new Brush(brush_style, inner, hatch_type, bm);
}

Rect::Rect(const Point left_top, const Point right_bottom,
		   const StandartColors inner, const StandartColors contour,
		   const PenStyle pen_style, const int32_t width,
		   const BrushStyle brush_style, const HatchTypes hatch_type,
		   const HBITMAP bm) {
	vertexes = new Point[2]{
		left_top,
		right_bottom
	};
	pen = new Pen(pen_style, width, contour);
	brush = new Brush(brush_style, inner, hatch_type, bm);
}

Rect::~Rect() {
	delete[] vertexes;
	delete pen;
	delete brush;
}

void Rect::Draw(const HDC hdc) {
	pen->Select(hdc);
	brush->Select(hdc);
	Rectangle(hdc, vertexes[0].x, vertexes[0].y, vertexes[1].x, vertexes[1].y);
}

void Rect::SetVertexes(const Point left_top, const Point right_bottom) {
	vertexes[0] = left_top;
	vertexes[1] = right_bottom;
}

void Rect::SetColor(const Color color) {
	pen->SetColor(color);
	brush->SetColor(color);
}

void Rect::SetColor(const StandartColors color) {
	pen->SetColor(color);
	brush->SetColor(color);
}

Circle::Circle() {
	vertexes = new Point[2]{
		{0, 0},
		{100, 100}
	};
	pen = new Pen();
	brush = new Brush();
}

Circle::Circle(const Point left_top, const Point right_bottom,
			   const Color inner, const Color contour,
			   const PenStyle pen_style, const int32_t width,
			   const BrushStyle brush_style, const HatchTypes hatch_type,
			   const HBITMAP bm) {
	vertexes = new Point[2]{
		left_top,
		right_bottom
	};
	pen = new Pen(pen_style, width, contour);
	brush = new Brush(brush_style, inner, hatch_type, bm);
}

Circle::Circle(const Point left_top, const Point right_bottom,
			   const StandartColors inner, const StandartColors contour,
			   const PenStyle pen_style, const int32_t width,
			   const BrushStyle brush_style, const HatchTypes hatch_type,
			   const HBITMAP bm) {
	vertexes = new Point[2]{
		left_top,
		right_bottom
	};
	pen = new Pen(pen_style, width, contour);
	brush = new Brush(brush_style, inner, hatch_type, bm);
}

Circle::~Circle() {
	delete[] vertexes;
	delete pen;
	delete brush;
}

void Circle::Draw(const HDC hdc) {
	pen->Select(hdc);
	brush->Select(hdc);
	Ellipse(hdc, vertexes[0].x, vertexes[0].y, vertexes[1].x, vertexes[1].y);
}

void Circle::SetColor(const Color color) {
	pen->SetColor(color);
	brush->SetColor(color);
}

void Circle::SetColor(const StandartColors color) {
	pen->SetColor(color);
	brush->SetColor(color);
}

void Circle::SetVertexes(const Point left_top, const Point right_bottom) {
	vertexes[0] = left_top;
	vertexes[1] = right_bottom;
}
