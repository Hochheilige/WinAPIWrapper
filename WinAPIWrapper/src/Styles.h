#pragma once

namespace Waw {

	enum class PenStyle : uint8_t {
		SOLID,
		DASH,
		DOT,
		DASHDOT,
		DASHDOTDOT,
		INVISIBLE,
		INSIDEFRAME
	};

	enum class BrushStyle : uint8_t {
		SOLID,
		HATCH,
		PATTERN
	};

	enum class HatchTypes : uint8_t {
		HORIZONTAL,
		VERTICAL,
		FDIAGONAL, // from left top to right bottom
		BDIAGONAL, // from left bottom to right top
		CROSS,
		DIAGCROSS,
	};

	enum class StandartColors : uint8_t {
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