#pragma once

#include "Color.h"

namespace Waw {

	class Brush {
	public:
		Brush();
		Brush(const BrushStyle st, const Color clr,
			  const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
			  const HBITMAP bm = nullptr);
		Brush(const BrushStyle st, const StandartColors clr,
			  const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
			  const HBITMAP bm = nullptr);

		void SetBrushStyle(const BrushStyle st,
						   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
						   const HBITMAP bm = nullptr);
		void SetHatch(const HatchTypes hatch_type);
		void SetColor(const Color clr);
		void SetColor(const StandartColors clr);
		void SetBitmap(const HBITMAP bm);
		void Select(const HDC hdc);
	private:
		HBRUSH brush;
		BrushStyle style;
		Color color;
		HatchTypes hatch;
		HBITMAP bitmap;

		void SelectStyle();
	};

}