#include "Figures.h"

namespace Waw {

	void Figure::SetColor(const Color color) {
		pen.SetColor(color);
		brush.SetColor(color);
	}

	void Figure::SetColor(const StandartColors color) {
		pen.SetColor(color);
		brush.SetColor(color);
	}
}
