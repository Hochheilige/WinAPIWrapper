#include "Pen.h"

namespace Waw {

	Pen::Pen() : style(PenStyle::SOLID), color(Color()), width(1) {
		pen = CreatePen(static_cast<uint8_t>(style), width, color.GetColorRef());
	}

	Pen::Pen(const PenStyle st, const Color clr, const int32_t w)
		: style(st), color(clr), width(w) {
		pen = CreatePen(static_cast<uint8_t>(style), width, color.GetColorRef());
	}

	Pen::Pen(const PenStyle st, const StandartColors clr, const int32_t w)
		: style(st), color(clr), width(w) {
		pen = CreatePen(static_cast<uint8_t>(style), width, color.GetColorRef());
	}

	void Pen::SetStyle(const PenStyle st) {
		style = st;
		DeleteObject(pen);
		pen = CreatePen(static_cast<uint8_t>(style), width, color.GetColorRef());
	}

	void Pen::SetWidth(const int32_t w) {
		width = w;
		DeleteObject(pen);
		pen = CreatePen(static_cast<uint8_t>(style), width, color.GetColorRef());
	}

	void Pen::Select(const HDC hdc) const {
		if (pen)
			SelectObject(hdc, pen);
	}

}