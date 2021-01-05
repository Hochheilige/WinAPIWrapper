#pragma once

#include <vector>

#include "Point.h"
#include "Color.h"
#include "Pen.h"
#include "Brush.h"

namespace Waw {

	class Figure {
	public:
		virtual void Draw(const HDC hdc) = 0;
		virtual void SetColor(const Color color) = 0;
		virtual void SetColor(const StandartColors color) = 0;

		inline void SetContourColor(const Color color) { pen.SetColor(color); }
		inline void SetContourColor(const StandartColors color) { pen.SetColor(color); }
		inline void SetContourStyle(const PenStyle style) { pen.SetStyle(style); }
		inline void SetContourWidth(const int32_t width) { pen.SetWidth(width); }
		inline void SetFillColor(const Color color) { brush.SetColor(color); }
		inline void SetFillColor(const StandartColors color) { brush.SetColor(color); }
		inline void SetFillStyle(const BrushStyle style,
								 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
								 const HBITMAP bm = nullptr) {
			brush.SetBrushStyle(style);
		}
		inline void SetFillHatch(const HatchTypes hatch_type) { brush.SetBrushStyle(BrushStyle::HATCH, hatch_type); }

	protected:
		std::vector<Point> vertexes;
		Pen pen;
		Brush brush;
	};

}