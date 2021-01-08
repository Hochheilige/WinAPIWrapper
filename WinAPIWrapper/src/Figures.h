#pragma once

#include <vector>

#include "Point.h"
#include "Color.h"
#include "Pen.h"
#include "Brush.h"

namespace Waw {

	class Figure {
	public:
		virtual void Draw() const = 0;

		void SetColor(const Color color);
		void SetColor(const StandartColors color);

		inline void SetContourColor(const Color color) { pen.SetColor(color); }
		inline void SetContourColor(const StandartColors color) { pen.SetColor(color); }
		inline void SetContourStyle(const PenStyle style) { pen.SetStyle(style); }
		inline void SetContourWidth(const int32_t width) { pen.SetWidth(width); }

		inline void SetFillColor(const Color color) { brush.SetColor(color); }
		inline void SetFillColor(const StandartColors color) { brush.SetColor(color); }
		inline void SetFillStyle(const BrushStyle style = BrushStyle::SOLID,
								 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
								 const HBITMAP bm = nullptr) {
			brush.SetBrushStyle(style, hatch_type, bm);
		}
		inline void SetFillHatch(const HatchTypes hatch_type) { brush.SetBrushStyle(BrushStyle::HATCH, hatch_type); }

		inline std::vector<Point> GetVertexes() { return vertexes; }
		inline Pen GetPen() { return pen; }
		inline Brush GetBrush() { return brush; }

	protected:
		std::vector<Point> vertexes;
		Pen pen;
		Brush brush;
	};

}