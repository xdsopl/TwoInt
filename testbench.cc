/*
Unsigned integer doubler

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <iostream>
#include <iomanip>

template <typename TYPE>
struct TwoInt
{
	TYPE lower, upper;
	TwoInt() : lower(0), upper(0) {}
	TwoInt(int value) : lower(value), upper(sizeof(int) <= sizeof(TYPE) ? 0 : value >> (sizeof(TYPE) * 8)) {}
	explicit operator bool () const
	{
		return lower || upper;
	}
	TwoInt<TYPE> operator|=(TwoInt<TYPE> a)
	{
		return *this = *this | a;
	}
	TwoInt<TYPE> operator&=(TwoInt<TYPE> a)
	{
		return *this = *this & a;
	}
	TwoInt<TYPE> operator^=(TwoInt<TYPE> a)
	{
		return *this = *this ^ a;
	}
	TwoInt<TYPE> operator>>=(int i)
	{
		return *this = *this >> i;
	}
	TwoInt<TYPE> operator<<=(int i)
	{
		return *this = *this << i;
	}
	TwoInt<TYPE> operator+=(TwoInt<TYPE> a)
	{
		return *this = *this + a;
	}
	TwoInt<TYPE> operator-=(TwoInt<TYPE> a)
	{
		return *this = *this - a;
	}
	TwoInt<TYPE> operator++()
	{
		if (!++lower)
			++upper;
		return *this;
	}
	TwoInt<TYPE> operator--()
	{
		if (!lower--)
			--upper;
		return *this;
	}
	TwoInt<TYPE> operator++(int)
	{
		TwoInt<TYPE> tmp = *this;
		++(*this);
		return tmp;
	}
	TwoInt<TYPE> operator--(int)
	{
		TwoInt<TYPE> tmp = *this;
		--(*this);
		return tmp;
	}
};

template <typename TYPE>
bool operator==(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	return a.upper == b.upper && a.lower == b.lower;
}

template <typename TYPE>
bool operator!=(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	return a.upper != b.upper || a.lower != b.lower;
}

template <typename TYPE>
bool operator<(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	return a.upper < b.upper || (a.upper == b.upper && a.lower < b.lower);
}

template <typename TYPE>
bool operator>(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	return a.upper > b.upper || (a.upper == b.upper && a.lower > b.lower);
}

template <typename TYPE>
bool operator<=(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	return a.upper < b.upper || (a.upper == b.upper && a.lower <= b.lower);
}

template <typename TYPE>
bool operator>=(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	return a.upper > b.upper || (a.upper == b.upper && a.lower >= b.lower);
}

template <typename TYPE>
TwoInt<TYPE> operator~(TwoInt<TYPE> a)
{
	TwoInt<TYPE> tmp;
	tmp.lower = ~a.lower;
	tmp.upper = ~a.upper;
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator|(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	TwoInt<TYPE> tmp;
	tmp.lower = a.lower | b.lower;
	tmp.upper = a.upper | b.upper;
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator&(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	TwoInt<TYPE> tmp;
	tmp.lower = a.lower & b.lower;
	tmp.upper = a.upper & b.upper;
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator^(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	TwoInt<TYPE> tmp;
	tmp.lower = a.lower ^ b.lower;
	tmp.upper = a.upper ^ b.upper;
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator>>(TwoInt<TYPE> a, int i)
{
	TwoInt<TYPE> tmp;
	int h = sizeof(TYPE) * 8;
	if (i > h)
		tmp.lower = a.upper >> (i - h);
	else
		tmp.lower = (a.lower >> i) | (a.upper << (h - i));
	tmp.upper = a.upper >> i;
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator<<(TwoInt<TYPE> a, int i)
{
	TwoInt<TYPE> tmp;
	tmp.lower = a.lower << i;
	int h = sizeof(TYPE) * 8;
	if (i > h)
		tmp.upper = a.lower << (i - h);
	else
		tmp.upper = (a.upper << i) | (a.lower >> (h - i));
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator+(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	TwoInt<TYPE> tmp;
	tmp.lower = a.lower + b.lower;
	tmp.upper = a.upper + b.upper;
	if (tmp.lower < a.lower)
		++tmp.upper;
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator-(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	TwoInt<TYPE> tmp;
	tmp.lower = a.lower - b.lower;
	tmp.upper = a.upper - b.upper;
	if (tmp.lower > a.lower)
		--tmp.upper;
	return tmp;
}

template <typename TYPE>
std::ostream &operator<<(std::ostream &os, const TwoInt<TYPE> a)
{
	return os << a.upper << a.lower;
}

template <>
std::ostream &operator<<<uint8_t>(std::ostream &os, const TwoInt<uint8_t> a)
{
	return os << std::hex
		<< std::setw(2) << std::setfill('0') << (unsigned)a.upper
		<< std::setw(2) << std::setfill('0') << (unsigned)a.lower;
}

template <>
std::ostream &operator<<<uint16_t>(std::ostream &os, const TwoInt<uint16_t> a)
{
	return os << std::hex
		<< std::setw(4) << std::setfill('0') << a.upper
		<< std::setw(4) << std::setfill('0') << a.lower;
}

template <>
std::ostream &operator<<<uint32_t>(std::ostream &os, const TwoInt<uint32_t> a)
{
	return os << std::hex
		<< std::setw(8) << std::setfill('0') << a.upper
		<< std::setw(8) << std::setfill('0') << a.lower;
}

template <>
std::ostream &operator<<<uint64_t>(std::ostream &os, const TwoInt<uint64_t> a)
{
	return os << std::hex
		<< std::setw(16) << std::setfill('0') << a.upper
		<< std::setw(16) << std::setfill('0') << a.lower;
}

int main()
{
	if (0) {
		typedef TwoInt<uint8_t> u16;
		uint16_t a = 0;
		u16 b(0);
		for (int i = 0; i < (1 << 20); ++i) {
			++a;
			++b;
			assert(a == *reinterpret_cast<uint16_t *>(&b));
		}
		for (int i = 0; i < (1 << 20); ++i) {
			--a;
			--b;
			assert(a == *reinterpret_cast<uint16_t *>(&b));
		}
	}
	if (0) {
		typedef TwoInt<uint8_t> u16;
		for (int i = 0; i < 65536; ++i)
			for (int j = 0; j < 65536; ++j)
				assert((i == j) == (u16(i) == u16(j)));
		for (int i = 0; i < 65536; ++i)
			for (int j = 0; j < 65536; ++j)
				assert((i != j) == (u16(i) != u16(j)));
		for (int i = 0; i < 65536; ++i)
			for (int j = 0; j < 65536; ++j)
				assert((i < j) == (u16(i) < u16(j)));
		for (int i = 0; i < 65536; ++i)
			for (int j = 0; j < 65536; ++j)
				assert((i > j) == (u16(i) > u16(j)));
		for (int i = 0; i < 65536; ++i)
			for (int j = 0; j < 65536; ++j)
				assert((i <= j) == (u16(i) <= u16(j)));
		for (int i = 0; i < 65536; ++i)
			for (int j = 0; j < 65536; ++j)
				assert((i >= j) == (u16(i) >= u16(j)));
	}
	if (0) {
		typedef TwoInt<uint8_t> u16;
		for (int i = 0; i < 65536; ++i) {
			for (int j = 0; j <= 16; ++j) {
				uint16_t a = i >> j;
				u16 b = u16(i) >> j;
				assert(a == *reinterpret_cast<uint16_t *>(&b));
			}
		}
		for (int i = 0; i < 65536; ++i) {
			for (int j = 0; j <= 16; ++j) {
				uint16_t a = i << j;
				u16 b = u16(i) << j;
				assert(a == *reinterpret_cast<uint16_t *>(&b));
			}
		}
	}
	if (0) {
		typedef TwoInt<uint8_t> u16;
		for (int i = 0; i < 65536; ++i) {
			for (int j = 0; j < 65536; ++j) {
				uint16_t a = i + j;
				u16 b = u16(i) + u16(j);
				assert(a == *reinterpret_cast<uint16_t *>(&b));
			}
		}
		for (int i = 0; i < 65536; ++i) {
			for (int j = 0; j < 65536; ++j) {
				uint16_t a = i - j;
				u16 b = u16(i) - u16(j);
				assert(a == *reinterpret_cast<uint16_t *>(&b));
			}
		}
	}
	//TwoInt<TwoInt<TwoInt<TwoInt<uint8_t>>>> a(0), b(1);
	TwoInt<TwoInt<uint8_t>> a(0), b(1);
	std::cout << "sizeof(a) = " << sizeof(a) << std::endl;
	std::cout << (a + b) << " = " << a << " + " << b << std::endl;
	std::cout << (a - b) << " = " << a << " - " << b << std::endl;
	return 0;
}

