#pragma once

#include <cstdint>

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
private:
	Point* entry = nullptr, *destination = nullptr;
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
							 const HBITMAP bm = nullptr) { brush->SetBrushStyle(style); }
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

