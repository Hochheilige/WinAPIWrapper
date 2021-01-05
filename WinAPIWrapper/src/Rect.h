#pragma once

#include "Figures.h"

namespace Waw {

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

		void Draw(const HDC hdc) override;

		void SetColor(const Color color) override;
		void SetColor(const StandartColors color) override;
		void SetVertexes(const Point left_top, const Point right_bottom);
	};

}
