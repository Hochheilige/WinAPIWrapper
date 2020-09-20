#pragma once

#include <cstdint>
#include <vector>

#include "Window.h"

enum class Style {
	SOLID,
	DASH, 
	DOT,
	DASHDOT,
	DASHDOTDOT,
	INVISIBLE,
	INSIDEFRAME
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
	int64_t x, y;

	Point() : x(0), y(0) {}
	Point(const uint64_t x_coord, const uint64_t y_coord)
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
	Pen(const Style st, const int32_t w, const Color clr);
	Pen(const Style st, const int32_t w, const StandartColors clr);

	inline void SetStyle(const Style st) { style = st; }
	inline void SetWidth(const int32_t w) { width = w; }
	inline void SetColor(const Color clr) { color = clr; }
	void Select(const HDC hdc);
private:
	HPEN pen;
	Style style;
	int32_t width;
	Color color;
};

class Line {
public:
	Line();
	Line(const Point start, const Point finish, Pen pn = Pen());
	Line(Point* start, Point* finish, Pen* pn = new Pen());
	Line(Point* points[], Pen* pn = new Pen());
	Line(const Point start, const Point finish, Style style = Style::SOLID,
		 int32_t width = 1, StandartColors color = StandartColors::WHITE);
	Line(Point* start, Point* finish, Style style = Style::SOLID,
		 int32_t width = 1, StandartColors color = StandartColors::WHITE);
	Line(Point* points[], Style style = Style::SOLID,
		 int32_t width = 1, StandartColors color = StandartColors::WHITE);

	void Draw(const HDC hdc);
private:
	Point* entry, *destination;
	Pen* pen;
};

class Figure {
public:

protected:

};

class Triangle : public Figure {
public:

	
private:

};

class Rect : public Figure {
public:

private:
	
};

class Circle : public Figure {
public:

private:

};

