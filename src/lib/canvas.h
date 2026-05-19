#ifndef __CANVAS_H_
#define __CANVAS_H_

#include <iostream>
#include <memory>
#include <vector>
#include "shape.h"

class Canvas {
public:
	Canvas() : _data() {}
	~Canvas() = default;

	// Copy Constructor
	// 觸發：MyString b = a; 或 MyString b(a);
    // 目的：做「深拷貝」，讓 b 有自己獨立的 data，不和 a 共用
	Canvas(const Canvas& other) {
		std::cout << "[Copy Constructor]" << std::endl;
		clearAndCopy(other);
	}

	// Copy Assignment Operator
	// 觸發：b = a;（b 已經存在，不是初始化）
	Canvas& operator=(const Canvas& other) {
		std::cout << "[Copy Assignment Constructor]" << std::endl;
		if (this != &other) {
			clearAndCopy(other);
		}

		return *this;
	}

private:
	std::vector<std::unique_ptr<Shape>> _data;

	void clearAndCopy(const Canvas& canvas) {
		_data.clear();
		for (auto& d : canvas._data) {
			_data.push_back(d->clone());
		}
	}
public:

	void add(std::unique_ptr<Shape> shape) {
		_data.push_back(move(shape));
	}

	void printAll() {
		for (auto& d : _data) {
			d->describe();
		}
	}
};

#endif