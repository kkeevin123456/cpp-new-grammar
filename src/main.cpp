#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ============================================================
//  練習起點：一個簡單的 Shape 繼承體系
//  你的任務：擴充它，加入更多 OOP 特性
// ============================================================

class Shape {
public:
    explicit Shape(std::string name) : name_(std::move(name)) {}
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual void describe() const {
        std::cout << "[" << name_ << "] area = " << area() << "\n";
    }

    const std::string& name() const { return name_; }

private:
    std::string name_;
};

class Circle : public Shape {
public:
    explicit Circle(double r) : Shape("Circle"), radius_(r) {}
    double area() const override { return 3.14159 * radius_ * radius_; }

private:
    double radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : Shape("Rectangle"), w_(w), h_(h) {}
    double area() const override { return w_ * h_; }

private:
    double w_, h_;
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));

    for (const auto& s : shapes) {
        s->describe();
    }
    return 0;
}