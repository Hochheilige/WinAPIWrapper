#pragma once

#include "Color.h"

namespace Waw {

	class Pen {
	public:
		Pen();
		Pen(const PenStyle st, const int32_t w, const Color clr);
		Pen(const PenStyle st, const int32_t w, const StandartColors clr);

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
		HPEN pen;
		PenStyle style;
		int32_t width;
		Color color;
	};

}