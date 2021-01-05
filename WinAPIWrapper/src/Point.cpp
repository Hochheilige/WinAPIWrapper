#include "Point.h"

namespace Waw {

	Point::Point() : x(0), y(0) {
	}

	Point::Point(const Point& point)
		: x(point.x), y(point.y) {
	}

	Point::Point(const int32_t x_coord, const int32_t y_coord) 
		: x(x_coord), y(y_coord) {
	}

}