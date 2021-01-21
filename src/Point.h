#pragma once

#include <cstdint>

namespace Waw {

	struct Point {
		int32_t x, y;

		Point();
		Point(const Point& point);
		Point(const int32_t x_coord, const int32_t y_coord);
	};

}