#include "Pen.h"

namespace Waw {

	Pen::Pen() : style(PenStyle::SOLID), width(1), color(Color()) {
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	Pen::Pen(const PenStyle st, const int32_t w, const Color clr)
		: style(st), width(w), color(clr) {
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	Pen::Pen(const PenStyle st, const int32_t w, const StandartColors clr)
		: style(st), width(w), color(clr) {
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	void Pen::SetStyle(const PenStyle st) {
		style = st;
		DeleteObject(pen);
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	void Pen::SetWidth(const int32_t w) {
		width = w;
		DeleteObject(pen);
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	void Pen::Select(const HDC hdc) const {
		if (pen)
			SelectObject(hdc, pen);
	}

}