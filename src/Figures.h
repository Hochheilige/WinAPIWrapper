#pragma once

#include <vector>
#include <memory>

#include <Point.h>
#include <Color.h>
#include <Pen.h>
#include <Brush.h>

namespace Waw {

	template <class T>
	class Figure {
	public:
		void Draw(HDC hdc) const { MakeFigure().Draw(hdc); }

		template <typename ColorType>
		void SetColor(const ColorType color) {
			pen->SetColor(color);
			brush->SetColor(color);
		}

		inline void SetContourColor(const Color color) { pen->SetColor(color); }
		inline void SetContourColor(const StandartColors color) { pen->SetColor(color); }
		inline void SetContourStyle(const PenStyle style) { pen->SetStyle(style); }
		inline void SetContourWidth(const int32_t width) { pen->SetWidth(width); }

		inline void SetFillColor(const Color color) { brush->SetColor(color); }
		inline void SetFillColor(const StandartColors color) { brush->SetColor(color); }
		inline void SetFillStyle(const BrushStyle style = BrushStyle::SOLID,
								 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
								 const HBITMAP bm = nullptr) {
			brush->SetBrushStyle(style, hatch_type, bm);
		}
		inline void SetFillHatch(const HatchTypes hatch_type) { brush->SetBrushStyle(BrushStyle::HATCH, hatch_type); }

		inline std::vector<Point> GetVertexes() const { return vertexes; }
		inline Pen GetPen() const { return pen; }
		inline Brush GetBrush() const { return brush; }

	private:
		std::vector<Point> vertexes;
		std::shared_ptr<Pen> pen;
		std::shared_ptr<Brush> brush;

		friend T;
		Figure() = default;

		inline T& MakeFigure() { return static_cast<T&>(*this); }
	};

}