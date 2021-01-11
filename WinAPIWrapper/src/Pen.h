#pragma once

#include "Color.h"

namespace Waw {

	class Pen {
	public:
		Pen();
		Pen(const PenStyle st, const Color clr, const int32_t w);
		Pen(const PenStyle st, const StandartColors clr, const int32_t w);

		void SetStyle(const PenStyle st);
		void SetWidth(const int32_t w);

	    template <typename ColorType>
		void SetColor(const ColorType clr) {
			color = Color(clr);
			DeleteObject(pen);
			pen = CreatePen(static_cast<uint8_t>(style), width, color.GetColorRef());
		}

		void Select(const HDC hdc) const;

	private:
		PenStyle style;
		Color color;
		int32_t width;
		HPEN pen;
	};

}