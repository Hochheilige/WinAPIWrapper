#include <Line.h>

namespace Waw {

	Line::Line(): entry({ 0, 0 }), destination({ 1,1 }), pen(Pen()) {
	}

	Line::Line(const Point start, const Point finish, Pen pn)
		: entry(start), destination(finish), pen(pn) {
	}

	Line::Line(const Point start, const Point finish,
			   PenStyle style, int32_t width, StandartColors color)
		: entry(start), destination(finish), pen({ style, color, width }) {
	}

	Line::~Line() {
	}

	void Line::Draw(HDC hdc) const {
		pen.Select(hdc);
		MoveToEx(hdc, entry.x, entry.y, nullptr);
		LineTo(hdc, destination.x, destination.y);
		DeleteObject(pen.GetPen());
	}

	void Line::SetCoord(const Point start, const Point finish) {
		entry = start;
		destination = finish;
	}

}