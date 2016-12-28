#pragma once

template<typename Left, typename Op, typename Right> class Expression {
	const Left& m_left;
	const Right& m_right;
public:
	typedef typename Left::value_type value_type;
	Expression(const Left& l, const Right& r) : m_left{ l }, m_right{ r } {}
	
	size_t size() const { return m_left.size(); }
	
	friend value_type operator[](int i) const {
		return Op::apply<value_type>(m_left[i], m_right[i]);
	}

	friend ostream& operator<< (ostream &os, const Expression& e) {
		os << "[ ";
		for (size_t i = 0; i < e.size(); i++) {
			os << ", " << e[i];
		}
		os << " ]";
		return os;
	}

	template<typename Left, typename Right>
	friend Expression<Left, Add, Right> operator+(const Left& l, const Right& r) {
		return Expression<Left, Add, Right>(l, r);
	}

	template<typename Left, typename Right>
	friend Expression<Left, Substraction, Right> operator-(const Left& l, const Right& r) {
		return Expression<Left, Substraction, Right>(l, r);
	}

	template<typename Left, typename Right>
	friend Expression<Left, Multiplication, Right> operator*(const Left& l, const Right& r) {
		return Expression<Left, Multiplication, Right>(l, r);
	}

	template<typename Left, typename Right>
	friend Expression<Left, Division, Right> operator/(const Left& l, const Right& r) {
		return Expression<Left, Division, Right>(l, r);
	}
};

struct Add {
	template<typename T> static T apply(T l, T r) {
		return l + r;
	}
};

struct Substraction {
	template<typename T> static T apply(T l, T r) {
		return l - r;
	}
};

struct Multiplication {
	template<typename T> static T apply(T l, T r) {
		return l * r;
	}
};

struct Division {
	template<typename T> static T apply(T l, T r) {
		return l / r;
	}
};