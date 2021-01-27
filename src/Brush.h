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

		~Brush();

		void SetBrushStyle(const BrushStyle st,
						   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
						   const HBITMAP bm = nullptr);

		void SetHatch(const HatchTypes hatch_type);
		void SetBitmap(const HBITMAP bm);

		template <typename ColorType>
		void SetColor(const ColorType clr) {
			color = Color(clr);
			if (brush)
				DeleteObject(brush);
			SelectStyle();
		}

		void Select(const HDC hdc) const;
	private:
		HBRUSH brush;
		BrushStyle style;
		Color color;
		HatchTypes hatch;
		HBITMAP bitmap;

		void SelectStyle();
	};

}