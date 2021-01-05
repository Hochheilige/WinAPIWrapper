#pragma once

#include <cstdint>

#include "Window.h"
#include "Styles.h"

namespace Waw {

	struct Color {
		uint16_t red, green, blue;

		Color();
		Color(const uint16_t r, const uint16_t g, const uint16_t b);
		explicit Color(const StandartColors color);

		COLORREF GetColorRef() const;
	};

}