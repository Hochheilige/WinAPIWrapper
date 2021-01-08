#include "Circle.h"

namespace Waw {

	Circle::Circle() {
		vertexes = {
			{0, 0},
			{100, 100}
		};
		pen = Pen();
		brush = Brush();
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
		pen = Pen(pen_style, width, contour);
		brush = Brush(brush_style, inner, hatch_type, bm);
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
		pen = Pen(pen_style, width, contour);
		brush = Brush(brush_style, inner, hatch_type, bm);
	}

	void Circle::Draw() const {
		Window* wnd = Window::GetInstance();
		HDC hdc = GetDC(wnd->GetWindow());
		pen.Select(hdc);
		brush.Select(hdc);
		Ellipse(hdc, vertexes[0].x, vertexes[0].y, vertexes[1].x, vertexes[1].y);
		ReleaseDC(wnd->GetWindow(), hdc);
	}

	void Circle::SetVertexes(const Point left_top, const Point right_bottom) {
		vertexes[0] = left_top;
		vertexes[1] = right_bottom;
	}

}