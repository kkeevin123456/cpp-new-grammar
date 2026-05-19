#ifndef __CANVAS_H_
#define __CANVAS_H_

#include <iostream>
#include "shape.h"

class Canvas {
public:
	Canvas(Shape** shapes = nullptr, int len = 0) : _data(shapes), _len(len) {}
	~Canvas() {
		release();
	}

	// Copy Constructor
	// 觸發：MyString b = a; 或 MyString b(a);
    // 目的：做「深拷貝」，讓 b 有自己獨立的 data，不和 a 共用
	Canvas(const Canvas& other) {
		std::cout << "[Copy Constructor]" << std::endl;
		deepCopy(other);
	}

	// Copy Assignment Operator
	// 觸發：b = a;（b 已經存在，不是初始化）
	Canvas& operator=(const Canvas& other) {
		std::cout << "[Copy Assignment Constructor]" << std::endl;
		if (this != &other) {
			release();

			deepCopy(other);
		}

		return *this;
	}

	// Move Constructor
	// 觸發：MyString b = std::move(a);
    // 目的：「偷走」a 的資源，不做 copy，效能更好
	Canvas(Canvas&& other) noexcept {
		std::cout << "[Move Constructor]" << std::endl;
		_data = other._data;
		_len = other._len;
		other._data = nullptr;
		other._len = 0;
	}

	// Move Assignment Operator
    // 觸發：b = std::move(a);（b 已存在）
	Canvas& operator=(Canvas&& other) noexcept {
		std::cout << "[Move Assignment Operator]" << std::endl;

		if (this != &other) {
			release();

			_data = other._data;
			_len = other._len;
			other._data = nullptr;
			other._len = 0;
		}

		return *this;
	}

private:
	Shape** _data;
	int _len;

	void release() {
		for (int i = 0; i < _len; i++) {
			delete _data[i];
		}
		delete[] _data;
		_len = 0;
	}

	void deepCopy(const Canvas& canvas) {
		_len = canvas._len;
		_data = new Shape*[_len];
		for (int i = 0; i < _len; i++) {
			_data[i] = canvas._data[i]->clone().release();
		}
	}
public:

	void add(Shape* shape) {
		_len++;
		Shape** new_data = new Shape*[_len];

		for (int i = 0; i < _len-1; i++) {
			new_data[i] = _data[i];
		}

		new_data[_len-1] = shape;
		delete[] _data;

		_data = new_data;
	}

	void printAll() {
		for (int i = 0; i < _len; i++) {
			_data[i]->describe();
		}
	}
};

#endif