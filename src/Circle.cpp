#include "Circle.h"

namespace Waw {

	Circle::Circle() {
		vertexes = {
			{0, 0},
			{100, 100}
		};
		pen.reset(new Pen());
		brush.reset(new Brush());
	}

	Circle::Circle(const Point left_top, const Point right_bottom,
				   const Color inner, const Color contour,
				   const PenStyle pen_style, const int32_t width,
				   const BrushStyle brush_style, const HatchTypes hatch_type,
				   const HBITMAP bm) {
		vertexes = {
			left_top,
			right_bottom
		};
		pen.reset(new Pen{ pen_style, contour, width });
		brush.reset(new Brush{ brush_style, inner, hatch_type, bm });
	}

	Circle::Circle(const Point left_top, const Point right_bottom,
				   const StandartColors inner, const StandartColors contour,
				   const PenStyle pen_style, const int32_t width,
				   const BrushStyle brush_style, const HatchTypes hatch_type,
				   const HBITMAP bm) {
		vertexes = {
			left_top,
			right_bottom
		};
		pen.reset(new Pen{ pen_style, contour, width });
		brush.reset(new Brush{ brush_style, inner, hatch_type, bm });
	}

	void Circle::Draw(HDC hdc) const {
		pen->Select(hdc);
		brush->Select(hdc);
		Ellipse(hdc, vertexes[0].x, vertexes[0].y, vertexes[1].x, vertexes[1].y);
	}

	void Circle::SetVertexes(const Point left_top, const Point right_bottom) {
		vertexes[0] = left_top;
		vertexes[1] = right_bottom;
	}

}