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


private:
	Point* entry, *destination;
	Pen* pen;
};

class Figure {
public:
	virtual void Draw(const HDC& hdc) = 0;
	virtual void SetLine(Style style, uint32_t width, StandartColors clr) = 0;
	virtual void SetLine(Style style, uint32_t width) = 0;
	virtual void SetColor(StandartColors color) = 0;
protected:
	Line line;
};

class Triangle : public Figure {
public:
	Triangle();
	Triangle(StandartColors color);
	Triangle(Line::Point* const v, StandartColors color = StandartColors::WHITE);
	Triangle(const Line::Point& v1, const Line::Point& v2, const Line::Point& v3, StandartColors color = StandartColors::WHITE);
	~Triangle();

	void Draw(const HDC& hdc) override;
	void SetLine(Style style, uint32_t width, StandartColors clr) override;
	void SetLine(Style style, uint32_t width) override;
	void SetColor(StandartColors color) override;
	void SetVertexes(Line::Point* const v);
	void SetVertexes(const Line::Point& v1, const Line::Point& v2, const Line::Point& v3);
	
private:
	Line::Point* vertexes = new Line::Point[3]();
	HBRUSH brush;
};

class Rect : public Figure {
public:

private:
	Line::Point* vertexes = new Line::Point[2]();
};

class Circle : public Figure {
public:

private:
	Line::Point* centre = new Line::Point();
	uint32_t radius;
};

