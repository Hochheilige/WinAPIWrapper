#include <WinAPIWrapper.h>

#include <iostream>
#include <vector>
#include <variant>

using namespace Waw;

template <typename... Ts>
using poly_T = std::variant<Ts...>;

using container_type = std::vector<
	poly_T<Triangle, Rect, Circle>
>;

int main() {
	Triangle tr({ 50, 250 }, { 650, 250 }, { 350, 150 }, StandartColors::GREEN);
	Rect rectangle({ 300, 300 }, { 400, 400 }, StandartColors::CYAN);
	tr.SetFillHatch(HatchTypes::DIAGCROSS);
	tr.SetColor(StandartColors::YELLOW);
	Circle circle({ 200, 200 }, {500, 500}, StandartColors::MAGENTA);

	container_type figures = { circle, tr, rectangle  };
	for (const auto& figure : figures)
		std::visit([](auto& fig) { fig.Draw(); }, figure);

	Line* line = new Line({500, 420}, {200, 420}, PenStyle::DOT, 6, StandartColors::GREEN);
	line->Draw();

	std::cin.get();
} 