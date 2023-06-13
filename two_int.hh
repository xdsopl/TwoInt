/*
Unsigned integer doubler

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

template <typename TYPE>
struct TwoInt
{
	TYPE lower, upper;
	TwoInt() : lower(0), upper(0) {}
	TwoInt(uint64_t value) : lower(value), upper(8 <= sizeof(TYPE) ? 0 : value >> (sizeof(TYPE) * 8)) {}
	static TwoInt<TYPE> one()
	{
		TwoInt<TYPE> tmp;
		tmp.lower = TYPE::one();
		return tmp;
	}
	static TwoInt<TYPE> max()
	{
		TwoInt<TYPE> tmp;
		tmp.lower = TYPE::max();
		tmp.upper = TYPE::max();
		return tmp;
	}
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
	TwoInt<TYPE> operator*=(TwoInt<TYPE> a)
	{
		return *this = *this * a;
	}
	TwoInt<TYPE> operator/=(TwoInt<TYPE> a)
	{
		return *this = *this / a;
	}
	TwoInt<TYPE> operator%=(TwoInt<TYPE> a)
	{
		return *this = *this % a;
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

template <>
TwoInt<uint8_t> TwoInt<uint8_t>::one()
{
	TwoInt<uint8_t> tmp;
	tmp.lower = 1;
	return tmp;
}

template <>
TwoInt<uint16_t> TwoInt<uint16_t>::one()
{
	TwoInt<uint16_t> tmp;
	tmp.lower = 1;
	return tmp;
}

template <>
TwoInt<uint32_t> TwoInt<uint32_t>::one()
{
	TwoInt<uint32_t> tmp;
	tmp.lower = 1;
	return tmp;
}

template <>
TwoInt<uint8_t> TwoInt<uint8_t>::max()
{
	TwoInt<uint8_t> tmp;
	tmp.lower = 255;
	tmp.upper = 255;
	return tmp;
}

template <>
TwoInt<uint16_t> TwoInt<uint16_t>::max()
{
	TwoInt<uint16_t> tmp;
	tmp.lower = 65535;
	tmp.upper = 65535;
	return tmp;
}

template <>
TwoInt<uint32_t> TwoInt<uint32_t>::max()
{
	TwoInt<uint32_t> tmp;
	tmp.lower = 4294967295;
	tmp.upper = 4294967295;
	return tmp;
}

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
	if (i == 0)
		return a;
	TwoInt<TYPE> tmp;
	int h = sizeof(TYPE) * 8;
	if (i < h) {
		tmp.lower = (a.lower >> i) | (a.upper << (h - i));
		tmp.upper = a.upper >> i;
	} else if (i < 2 * h) {
		tmp.lower = a.upper >> (i - h);
	}
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator<<(TwoInt<TYPE> a, int i)
{
	if (i == 0)
		return a;
	TwoInt<TYPE> tmp;
	int h = sizeof(TYPE) * 8;
	if (i < h) {
		tmp.lower = a.lower << i;
		tmp.upper = (a.upper << i) | (a.lower >> (h - i));
	} else if (i < 2 * h) {
		tmp.upper = a.lower << (i - h);
	}
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
TwoInt<TYPE> operator*(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	TwoInt<TYPE> middle = mul(a.lower, b.upper) + mul(a.upper, b.lower);
	int h = sizeof(TYPE) * 8;
	return mul(a.lower, b.lower) + (middle << h);
}

TwoInt<uint8_t> operator*(TwoInt<uint8_t> a, TwoInt<uint8_t> b)
{
	uint16_t tmp = *reinterpret_cast<uint16_t *>(&a) * *reinterpret_cast<uint16_t *>(&b);
	return *reinterpret_cast<TwoInt<uint8_t> *>(&tmp);
}

TwoInt<uint16_t> operator*(TwoInt<uint16_t> a, TwoInt<uint16_t> b)
{
	uint32_t tmp = *reinterpret_cast<uint32_t *>(&a) * *reinterpret_cast<uint32_t *>(&b);
	return *reinterpret_cast<TwoInt<uint16_t> *>(&tmp);
}

TwoInt<uint32_t> operator*(TwoInt<uint32_t> a, TwoInt<uint32_t> b)
{
	uint64_t tmp = *reinterpret_cast<uint64_t *>(&a) * *reinterpret_cast<uint64_t *>(&b);
	return *reinterpret_cast<TwoInt<uint32_t> *>(&tmp);
}

template <typename TYPE>
TwoInt<TwoInt<TYPE>> mul(TwoInt<TYPE> a, TwoInt<TYPE> b)
{
	TwoInt<TYPE> middle;
	middle = mul(a.lower, b.upper) + mul(a.upper, b.lower);
	int h = sizeof(TYPE) * 8;
	TwoInt<TYPE> lower = middle << h;
	TwoInt<TYPE> upper = middle >> h;
	TwoInt<TwoInt<TYPE>> tmp;
	tmp.lower = mul(a.lower, b.lower) + lower;
	tmp.upper = mul(a.upper, b.upper) + upper;
	if (tmp.lower < lower)
		++tmp.upper;
	return tmp;
}

template <>
TwoInt<TwoInt<uint8_t>> mul(TwoInt<uint8_t> a, TwoInt<uint8_t> b)
{
	uint32_t tmp = uint32_t(*reinterpret_cast<uint16_t *>(&a)) * uint32_t(*reinterpret_cast<uint16_t *>(&b));
	return *reinterpret_cast<TwoInt<TwoInt<uint8_t>> *>(&tmp);
}

template <>
TwoInt<TwoInt<uint16_t>> mul(TwoInt<uint16_t> a, TwoInt<uint16_t> b)
{
	uint64_t tmp = uint64_t(*reinterpret_cast<uint32_t *>(&a)) * uint64_t(*reinterpret_cast<uint32_t *>(&b));
	return *reinterpret_cast<TwoInt<TwoInt<uint16_t>> *>(&tmp);
}

template <>
TwoInt<TwoInt<uint32_t>> mul(TwoInt<uint32_t> a, TwoInt<uint32_t> b)
{
	uint64_t middle = uint64_t(a.lower) * uint64_t(b.upper) + uint64_t(a.upper) * uint64_t(b.lower);
	uint64_t lower = uint64_t(a.lower) * uint64_t(b.lower) + (middle << 32);
	uint64_t upper = uint64_t(a.upper) * uint64_t(b.upper) + (middle >> 32);
	if (lower < (middle << 32))
		++upper;
	TwoInt<TwoInt<uint32_t>> tmp;
	tmp.lower = *reinterpret_cast<TwoInt<uint32_t> *>(&lower);
	tmp.upper = *reinterpret_cast<TwoInt<uint32_t> *>(&upper);
	return tmp;
}

template <typename TYPE>
TwoInt<TYPE> operator/(TwoInt<TYPE> dividend, TwoInt<TYPE> divisor)
{
	assert(divisor);
	TwoInt<TYPE> quotient, one(1);
	for (int shift = sizeof(one) * 8 - 1; shift >= 0; --shift) {
		if ((dividend >> shift) >= divisor) {
			dividend -= divisor << shift;
			quotient |= one << shift;
		}
	}
	return quotient;
}

TwoInt<uint8_t> operator/(TwoInt<uint8_t> a, TwoInt<uint8_t> b)
{
	uint16_t tmp = *reinterpret_cast<uint16_t *>(&a) / *reinterpret_cast<uint16_t *>(&b);
	return *reinterpret_cast<TwoInt<uint8_t> *>(&tmp);
}

TwoInt<uint16_t> operator/(TwoInt<uint16_t> a, TwoInt<uint16_t> b)
{
	uint32_t tmp = *reinterpret_cast<uint32_t *>(&a) / *reinterpret_cast<uint32_t *>(&b);
	return *reinterpret_cast<TwoInt<uint16_t> *>(&tmp);
}

TwoInt<uint32_t> operator/(TwoInt<uint32_t> a, TwoInt<uint32_t> b)
{
	uint64_t tmp = *reinterpret_cast<uint64_t *>(&a) / *reinterpret_cast<uint64_t *>(&b);
	return *reinterpret_cast<TwoInt<uint32_t> *>(&tmp);
}

template <typename TYPE>
TwoInt<TYPE> operator%(TwoInt<TYPE> dividend, TwoInt<TYPE> divisor)
{
	assert(divisor);
	TwoInt<TYPE> quotient;
	for (int shift = sizeof(quotient) * 8 - 1; shift >= 0; --shift)
		if ((dividend >> shift) >= divisor)
			dividend -= divisor << shift;
	return dividend;
}

TwoInt<uint8_t> operator%(TwoInt<uint8_t> a, TwoInt<uint8_t> b)
{
	uint16_t tmp = *reinterpret_cast<uint16_t *>(&a) % *reinterpret_cast<uint16_t *>(&b);
	return *reinterpret_cast<TwoInt<uint8_t> *>(&tmp);
}

TwoInt<uint16_t> operator%(TwoInt<uint16_t> a, TwoInt<uint16_t> b)
{
	uint32_t tmp = *reinterpret_cast<uint32_t *>(&a) % *reinterpret_cast<uint32_t *>(&b);
	return *reinterpret_cast<TwoInt<uint16_t> *>(&tmp);
}

TwoInt<uint32_t> operator%(TwoInt<uint32_t> a, TwoInt<uint32_t> b)
{
	uint64_t tmp = *reinterpret_cast<uint64_t *>(&a) % *reinterpret_cast<uint64_t *>(&b);
	return *reinterpret_cast<TwoInt<uint32_t> *>(&tmp);
}

template <typename TYPE>
TwoInt<TwoInt<TYPE>> div(TwoInt<TYPE> dividend, TwoInt<TYPE> divisor)
{
	assert(divisor);
	TwoInt<TYPE> quotient, remainder, one(1);
	for (int shift = sizeof(one) * 8 - 1; shift >= 0; --shift) {
		remainder <<= 1;
		remainder |= (dividend >> shift) & one;
		if (remainder >= divisor) {
			remainder -= divisor;
			quotient |= one << shift;
		}
	}
	TwoInt<TwoInt<TYPE>> tmp;
	tmp.lower = quotient;
	tmp.upper = remainder;
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

