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
	}

	Triangle::Triangle(const Point v1, const Point v2, const Point v3,
					   const Color inner, const Color contour,
					   const PenStyle pen_style, const int32_t width,
					   const BrushStyle brush_style, const HatchTypes hatch_type,
					   const HBITMAP bm) {
		vertexes = { v1, v2, v3 };
		pen.reset(new Pen{ pen_style, contour, width });
		brush.reset(new Brush{ brush_style, inner, hatch_type, bm });
	}

	Triangle::Triangle(const Point v1, const Point v2, const Point v3,
					   const StandartColors inner, const StandartColors contour,
					   const PenStyle pen_style, const int32_t width,
					   const BrushStyle brush_style, const HatchTypes hatch_type,
					   const HBITMAP bm) {
		vertexes = { v1, v2, v3 };
		pen.reset(new Pen{ pen_style, contour, width });
		brush.reset(new Brush{ brush_style, inner, hatch_type, bm });
	}

	void Triangle::Draw(HDC hdc) const {
		pen->Select(hdc);
		brush->Select(hdc);
		POINT* points = new POINT[3]{
			{ vertexes[0].x, vertexes[0].y },
			{ vertexes[1].x, vertexes[1].y },
			{ vertexes[2].x, vertexes[2].y }
		};
		Polygon(hdc, points, 3);

		delete[] points;
	}

	void Triangle::SetVertexes(const Point v1, const Point v2, const Point v3) {
		vertexes[0] = v1;
		vertexes[1] = v2;
		vertexes[2] = v3;
	}
}