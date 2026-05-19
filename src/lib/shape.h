#ifndef __SHAPE_H_
#define __SHAPE_H_

#include <iostream>
#include <memory>
#include <string>
#include <concepts>

class Shape {
public:
    explicit Shape(std::string name) : name_(std::move(name)) {}
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual void describe() const {
        std::cout << "[" << name_ << "] area = " << area() << "\n";
    }

    const std::string& name() const { return name_; }

	virtual std::unique_ptr<Shape> clone() const = 0;

private:
    std::string name_;
};

class Circle : public Shape {
public:
    explicit Circle(double r) : Shape("Circle"), radius_(r) {}
    double area() const override { return 3.14159 * radius_ * radius_; }
	std::unique_ptr<Shape> clone() const override {
		return std::make_unique<Circle>(*this);
	}

private:
    double radius_;
};

class Rectangle : public Shape {
public:
    explicit Rectangle(double w, double h) : Shape("Rectangle"), w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
	std::unique_ptr<Shape> clone() const override {
		return std::make_unique<Rectangle>(*this);
	}

private:
    double w_, h_;
};

class Triangle : public Shape {
public:
	explicit Triangle(double base, double h) : Shape("Triangle"), base_(base), h_(h) {}
	double area() const override { return base_ * h_ / 2;}
	std::unique_ptr<Shape> clone() const override {
		return std::make_unique<Triangle>(*this);
	}

private:
	double base_, h_;
};

template<typename T>
concept Describable = requires(T s) {
	{ s.area() } -> std::floating_point;
	{ s.describe() } -> std::same_as<void>;
};

template<Describable T>
void printShape(const T& shape) {
	shape.describe();
};

#endif