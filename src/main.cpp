#include <vector>
#include <memory>
#include "shape.h"
#include "canvas.h"

int main() {
    //std::vector<std::unique_ptr<Shape>> shapes;
    //shapes.push_back(std::make_unique<Circle>(5.0));
    //shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    //shapes.push_back(std::make_unique<Triangle>(4.0, 6.0));

    //for (const auto& s : shapes) {
    //    s->describe();
    //}

	Shape *circle = new Circle(5.0), *rectangle = new Rectangle(4.0, 6.0), *triangle = new Triangle(4.0, 6.0);
	Shape **data = new Shape*[3];
	data[0] = circle;
	data[1] = rectangle;

	Canvas canvas_a = Canvas(data, 2);
	canvas_a.add(triangle);

	Canvas canvas_b = canvas_a;
	canvas_a = canvas_b;

	Canvas canvas_c = std::move(canvas_a);
	canvas_c = std::move(canvas_b);

	canvas_c.printAll();

    return 0;
}