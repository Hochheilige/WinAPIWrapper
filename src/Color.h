#pragma once

#include <cstdint>

#include <Windows.h>
#include "Styles.h"

namespace Waw {

	struct Color {
		uint8_t red, green, blue;

		Color();
		Color(const uint8_t r, const uint8_t g, const uint8_t b);
		explicit Color(const StandartColors color);

		COLORREF GetColorRef() const;
	};

}