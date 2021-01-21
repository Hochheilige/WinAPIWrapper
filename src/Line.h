#pragma once

#include <cmath>

#include <Point.h>
#include <Pen.h>

namespace Waw {

	class Line {
	public:
		Line();
		Line(const Point start, const Point finish, const Pen pn = Pen());
		Line(const Point start, const Point finish, const PenStyle style = PenStyle::SOLID,
			 const int32_t width = 1, const StandartColors color = StandartColors::WHITE);

		void Draw(HDC hdc) const;
		void SetCoord(const Point start, const Point finish);

		inline void SetEntry(const Point start) { entry = start; }
		inline void SetDestination(const Point finish) { destination = finish; }
		inline void SetColor(const Color color) { pen.SetColor(color); }
		inline void SetColor(const StandartColors color) { pen.SetColor(color); }
		inline void SetStyle(const PenStyle style) { pen.SetStyle(style); }
		inline void SetWidth(const int32_t width) { pen.SetWidth(width); }

		inline int32_t GetLength() {
			return sqrt(pow((destination.x - entry.x), 2) +pow((destination.y - entry.y), 2));
		}
		inline Point GetEntry() { return { entry.x, entry.y }; }
		inline Point GetDestination() { return { destination.x, destination.y }; }

	private:
		Point entry, destination;
		Pen pen;
	};

}