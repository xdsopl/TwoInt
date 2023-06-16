/*
Polar code bit reliability sequence example

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <cassert>
#include <iostream>
#include <algorithm>
#include "two_int.hh"

template <typename TYPE, int ORDER>
struct PolarCodeConst0
{
	static const int LENGTH = 1 << ORDER;
	TYPE prob[LENGTH];
	void compute(TYPE pe, int i, int h)
	{
		if (h) {
			compute((pe << 1) - mul(pe, pe).upper, i, h/2);
			compute(mul(pe, pe).upper, i+h, h/2);
		} else {
			prob[i] = pe;
		}
	}
	int significant(int value) {
		int msb = 0;
		while (value >>= 1)
			++msb;
		return msb;
	}
	void operator()(int *sequence, int numerator = 1, int denominator = 2)
	{
		assert(numerator <= denominator);
		int bits = sizeof(TYPE) * 8;
		int shift = bits - 1 - significant(numerator);
		TYPE erasure_probability = TYPE(numerator) << shift;
		erasure_probability /= TYPE(denominator);
		if (erasure_probability.get(bits - 1))
			erasure_probability >>= 1;
		compute(erasure_probability, 0, LENGTH / 2);
		for (int i = 0; i < LENGTH; ++i)
			sequence[i] = i;
		std::sort(sequence, sequence+LENGTH, [this](int a, int b){ return prob[a] > prob[b]; });
	}
};

int main()
{
	const int ORDER = 10;
	const int LENGTH = 1 << ORDER;
	typedef TwoInt<TwoInt<TwoInt<TwoInt<TwoInt<TwoInt<TwoInt<uint32_t>>>>>>> TYPE;
	std::cerr << "type bits: " << sizeof(TYPE) * 8 << std::endl;
	auto freeze = new PolarCodeConst0<TYPE, ORDER>();
	auto sequence = new int[LENGTH];
	(*freeze)(sequence, 3, 10);
	for (int i = 0; i < LENGTH; ++i)
		std::cout << " " << sequence[i];
	std::cout << std::endl;
	delete[] sequence;
	delete freeze;
	return 0;
}

