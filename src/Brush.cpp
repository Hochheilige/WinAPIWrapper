#include "Brush.h"

namespace Waw {

	Brush::Brush() {
		style = BrushStyle::SOLID;
		color = Color();
		hatch = HatchTypes::HORIZONTAL;
		bitmap = nullptr;
		brush = CreateSolidBrush(color.GetColorRef());
	}

	Brush::Brush(const BrushStyle st, const Color clr, const HatchTypes hatch_type, 
				 const HBITMAP bm) {
		style = st;
		color = clr;
		hatch = hatch_type;
		bitmap = bm;
		SelectStyle();
	}

	Brush::Brush(const BrushStyle st, const StandartColors clr, const HatchTypes hatch_type, 
				 const HBITMAP bm) {
		style = st;
		color = Color(clr);
		hatch = hatch_type;
		bitmap = bm;
		SelectStyle();
	}

	Brush::~Brush() {
		DeleteObject(brush);
	}

	void Brush::SetBrushStyle(const BrushStyle st, const HatchTypes hatch_type, 
							  const HBITMAP bm) {
		style = st;
		hatch = hatch_type;
		bitmap = bm;
		if (brush)
			DeleteObject(brush);
		SelectStyle();
	}

	void Brush::SetHatch(const HatchTypes hatch_type) {
		hatch = hatch_type;
		if (brush)
			DeleteObject(brush);
		SelectStyle();
	}

	void Brush::SetBitmap(const HBITMAP bm) {
		bitmap = bm;
		if (brush)
			DeleteObject(brush);
		SelectStyle();
	}

	void Brush::Select(const HDC hdc) const {
		if (brush)
			SelectObject(hdc, brush);
	}

	void Brush::SelectStyle() {
		switch (style) {
			case BrushStyle::SOLID: {
				brush = CreateSolidBrush(color.GetColorRef());
				break;
			} case BrushStyle::HATCH: {
				brush = CreateHatchBrush(static_cast<int>(hatch), color.GetColorRef());
				break;
			} case BrushStyle::PATTERN: {
				brush = CreatePatternBrush(bitmap);
				break;
			}
		}
	}

}