#pragma once
#include <iostream>
#include <cstddef>
#include <array>
#include "Expression.h"

using namespace std;

template<typename T, unsigned int S>
class Vector : public std::array<T, S>
{
public:
	Vector() = default;
	Vector(const initializer_list<T>& data) {
		size_t s = __min(data.size(), S);
		auto it = data.begin()
		for (size_t i = 0; i < s; i++) this->at(i) = *it++;
	}

	friend ostream& operator<<(std::ostream& os, const Vector<T, S>& v) {
		os << "[ ";
		auto & it = v.begin();
		if (it != v.end()) os << *it++;
		while (it != v.end()) {
			os << ", " << *it++;
		}
		
		os << " ]";
		return os;
	}

	template <typename Left, typename Operator, typename Right>
	friend void operator=(Expression<Left, Operator, Right> expr) {
		for (size_t i = 0; i < S; i++) {
			this->at(i) = expr[i];
		}
	}

	template <typename Left, typename T>
	friend Expression<Left, Add, Vector<T, S>> operator+(Left a, Vector<T, S> b) {
		return Expression < Left, Add, Vector<T, S>>(a, b);
	}
};