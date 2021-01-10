#pragma once

#include <vector>

#include "Point.h"
#include "Color.h"
#include "Pen.h"
#include "Brush.h"

namespace Waw {

	template <class T>
	class Figure {
	public:
		void Draw() const { as_underlying().Draw(); }

		template <typename ColorType>
		void SetColor(const ColorType color) {
			pen.SetColor(color);
			brush.SetColor(color);
		}

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

		inline std::vector<Point> GetVertexes() const { return vertexes; }
		inline Pen GetPen() const { return pen; }
		inline Brush GetBrush() const { return brush; }

	protected:
		std::vector<Point> vertexes;
		Pen pen;
		Brush brush;

	private:
		friend T;
		Figure() = default;

		inline T& as_underlying() { return static_cast<T&>(*this); }
	};

}