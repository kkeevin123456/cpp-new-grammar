#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "./lib/shape.h"
#include "./lib/canvas.h"

int main() {
	Canvas canvas_a = Canvas();
	canvas_a.add(std::make_unique<Circle>(5.0));
	canvas_a.add(std::make_unique<Rectangle>(4.0, 6.0));
	canvas_a.add(std::make_unique<Triangle>(4.0, 6.0));

	Canvas canvas_b = canvas_a;
	canvas_a = canvas_b;

	Canvas canvas_c = std::move(canvas_a);
	canvas_c = std::move(canvas_b);

	canvas_c.printAll();

	std::vector<std::string> names = canvas_c.filterNames(15);
	std::ranges::for_each(names, [](const std::string& name) {
		std::cout << name << "\n";
	});

    return 0;
}