#pragma once

namespace Waw {

	enum class PenStyle {
		SOLID,
		DASH,
		DOT,
		DASHDOT,
		DASHDOTDOT,
		INVISIBLE,
		INSIDEFRAME
	};

	enum class BrushStyle {
		SOLID,
		HATCH,
		PATTERN
	};

	enum class HatchTypes {
		HORIZONTAL,
		VERTICAL,
		FDIAGONAL, // from left top to right bottom
		BDIAGONAL, // from left bottom to right top
		CROSS,
		DIAGCROSS,
	};

	enum class StandartColors {
		WHITE,
		BLACK,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		MAGENTA
	};

}