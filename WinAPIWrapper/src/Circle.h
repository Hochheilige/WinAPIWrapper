#pragma once

#include "Figures.h"

namespace Waw {

	class Circle : public Figure<Circle> {
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

		void Draw() const;

		void SetVertexes(const Point left_top, const Point right_bottom);
	};

}
