#include "Triangle.h"

namespace Waw {

	Triangle::Triangle() {
		vertexes = {
			{ 100, 0   },
			{ 0  , 100 },
			{ 100, 100 }
		};
		pen.reset(new Pen());
		brush.reset(new Brush());
		points = new POINT[3];
		for (int i = 0; i < 3; ++i)
			points[i] = { vertexes[i].x, vertexes[i].y };
	}

	Triangle::Triangle(const Triangle& tr) {
		vertexes = tr.GetVertexes();
		pen = tr.GetPen();
		brush = tr.GetBrush();

		if (!points)
			points = new POINT[3];

		for (int i = 0; i < 3; ++i)
			points[i] = { vertexes[i].x, vertexes[i].y };
	}

	Triangle::Triangle(Triangle&& tr) {
		// No implement
	}

	Triangle::Triangle(const Point v1, const Point v2, const Point v3,
					   const Color inner, const Color contour,
					   const PenStyle pen_style, const int32_t width,
					   const BrushStyle brush_style, const HatchTypes hatch_type,
					   const HBITMAP bm) {
		vertexes = { v1, v2, v3 };
		pen.reset(new Pen{ pen_style, contour, width });
		brush.reset(new Brush{ brush_style, inner, hatch_type, bm });
		points = new POINT[3];
		for (int i = 0; i < 3; ++i)
			points[i] = { vertexes[i].x, vertexes[i].y };
	}

	Triangle::Triangle(const Point v1, const Point v2, const Point v3,
					   const StandartColors inner, const StandartColors contour,
					   const PenStyle pen_style, const int32_t width,
					   const BrushStyle brush_style, const HatchTypes hatch_type,
					   const HBITMAP bm) {
		vertexes = { v1, v2, v3 };
		pen.reset(new Pen{ pen_style, contour, width });
		brush.reset(new Brush{ brush_style, inner, hatch_type, bm });
		points = new POINT[3];
		for (int i = 0; i < 3; ++i)
			points[i] = { vertexes[i].x, vertexes[i].y };
	}

	Triangle::~Triangle() {
		if (points)
			delete[] points;
	}

	void Triangle::Draw(HDC hdc) const {
		pen->Select(hdc);
		brush->Select(hdc);
		Polygon(hdc, points, 3);
	}

	void Triangle::SetVertexes(const Point v1, const Point v2, const Point v3) {
		vertexes[0] = v1;
		vertexes[1] = v2;
		vertexes[2] = v3;

		for (int i = 0; i < 3; ++i)
			points[i] = { vertexes[i].x, vertexes[i].y };
	}
}