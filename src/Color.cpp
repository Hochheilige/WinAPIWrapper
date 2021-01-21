#include <Color.h>

namespace Waw {

	Color::Color() : red(255), green(255), blue(255) {
	}

	Color::Color(const uint8_t r, const uint8_t g, const uint8_t b) 
		: red(r), green(g), blue(b) {
	
	}

	Color::Color(const StandartColors color) {
		switch (color) {
			case StandartColors::WHITE: {
				red = green = blue = 255;
				break;
			} case StandartColors::BLACK: {
				red = green = blue = 0;
				break;
			} case StandartColors::RED: {
				red = 255;
				green = blue = 0;
				break;
			} case StandartColors::GREEN: {
				green = 255;
				red = blue = 0;
				break;
			} case StandartColors::BLUE: {
				blue = 255;
				red = green = 0;
				break;
			} case StandartColors::YELLOW: {
				red = green = 255;
				blue = 0;
				break;
			} case StandartColors::CYAN: {
				green = blue = 255;
				red = 0;
				break;
			} case StandartColors::MAGENTA: {
				red = blue = 255;
				green = 0;
				break;
			} default: {
				red = green = blue = 0;
				break;
			}
		}
	}

	COLORREF Color::GetColorRef() const {
		return RGB(red, green, blue);
	}

}