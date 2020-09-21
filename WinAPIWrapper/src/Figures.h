#pragma once

#include <cstdint>
#include <vector>

#include "Window.h"

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
		: x(x_coord), y(y_coord) {}
	Point(const Point& point) : x(point.x), y(point.y) {}
};

struct Color {
	uint16_t red, green, blue;

	Color() : red(255), green(255), blue(255) {}
	Color(uint16_t r, uint16_t g, uint16_t b) : red(r), green(g), blue(b) {}
	explicit Color(StandartColors color);

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
		  HBITMAP bm = nullptr);
	Brush(const BrushStyle st, const StandartColors clr,
		  const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		  HBITMAP bm = nullptr);

	void SetBrushStyle(const BrushStyle st, 
					   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
					   HBITMAP bm = nullptr);
	void SetHatch(HatchTypes hatch_type);
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
	Line(const Point start, const Point finish, Pen pn = Pen());
	Line(Point* start, Point* finish, Pen* pn = new Pen());
	Line(Point* points[], Pen* pn = new Pen());
	Line(const Point start, const Point finish, PenStyle style = PenStyle::SOLID,
		 int32_t width = 1, StandartColors color = StandartColors::WHITE);
	Line(Point* start, Point* finish, PenStyle style = PenStyle::SOLID,
		 int32_t width = 1, StandartColors color = StandartColors::WHITE);
	Line(Point* points[], PenStyle style = PenStyle::SOLID,
		 int32_t width = 1, StandartColors color = StandartColors::WHITE);

	void Draw(const HDC hdc);
private:
	Point* entry = nullptr, *destination = nullptr;
	Pen* pen = nullptr;
};

class Figure {
public:
	virtual void Draw(const HDC hdc) = 0;
protected:
	Point* vertexes = nullptr;
	Pen* pen = nullptr;
	Brush* brush = nullptr;
};

class Triangle : public Figure {
public:
	Triangle();

	void Draw(const HDC hdc) override;
};

class Rect : public Figure {
public:

private:
	
};

class Circle : public Figure {
public:

private:

};

