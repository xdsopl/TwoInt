/*
Polar code bit reliability sequence example

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <cassert>
#include <limits>
#include <iostream>
#include <algorithm>
#include "two_int.hh"

template <typename TYPE, int ORDER>
struct BhattacharyyaSequence
{
	static const int LENGTH = 1 << ORDER;
	TYPE prob[LENGTH];
	void compute(TYPE pe, int i, int h)
	{
		if (h) {
			compute((pe << 1) - (mul(pe, pe) << 1).upper, i, h/2);
			compute((mul(pe, pe) << 1).upper, i+h, h/2);
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
		int shift = significant(numerator);
		TYPE erasure_probability = TYPE(numerator) << bits - 1 - shift;
		erasure_probability /= TYPE(denominator);
		erasure_probability <<= shift;
		compute(erasure_probability, 0, LENGTH / 2);
		for (int i = 0; i < LENGTH; ++i)
			sequence[i] = i;
		std::stable_sort(sequence, sequence+LENGTH, [this](int a, int b){ return prob[a] > prob[b]; });
	}
};

// erasure probabilities above one half are stored as their negated
// complement, as values close to one would otherwise round to one.
// squares are kept above zero, so the sign survives underflow and
// doesn't depend on signed zeros, which -ffast-math ignores
template <int ORDER>
struct BhattacharyyaSequence<double, ORDER>
{
	typedef double TYPE;
	static const int LENGTH = 1 << ORDER;
	TYPE prob[LENGTH];
	void compute(TYPE pe, int i, int h)
	{
		if (h) {
			// 2x - x^2 and x^2 work for both z and 1 - z
			bool comp = pe < 0.0;
			TYPE x = comp ? -pe : pe;
			TYPE square = x * x;
			if (square < std::numeric_limits<TYPE>::min())
				square = std::numeric_limits<TYPE>::min();
			TYPE grow = 2.0 * x - x * x;
			bool flip = grow > 0.5;
			if (flip)
				grow = (1.0 - x) * (1.0 - x);
			if (comp != flip)
				grow = -grow;
			if (comp)
				square = -square;
			compute(comp ? square : grow, i, h/2);
			compute(comp ? grow : square, i+h, h/2);
		} else {
			prob[i] = pe;
		}
	}
	void operator()(int *sequence, int numerator = 1, int denominator = 2)
	{
		assert(numerator <= denominator);
		bool comp = 2 * numerator > denominator;
		TYPE erasure_probability = TYPE(comp ? denominator - numerator : numerator);
		erasure_probability /= TYPE(denominator);
		if (erasure_probability < std::numeric_limits<TYPE>::min())
			erasure_probability = std::numeric_limits<TYPE>::min();
		if (comp)
			erasure_probability = -erasure_probability;
		compute(erasure_probability, 0, LENGTH / 2);
		for (int i = 0; i < LENGTH; ++i)
			sequence[i] = i;
		std::stable_sort(sequence, sequence+LENGTH, [this](int a, int b){
			bool na = prob[a] < 0.0, nb = prob[b] < 0.0;
			return na != nb ? na : prob[a] > prob[b];
		});
	}
};

int main()
{
	const int ORDER = 10;
	const int LENGTH = 1 << ORDER;
	typedef TwoInt<TwoInt<TwoInt<TwoInt<TwoInt<TwoInt<TwoInt<uint32_t>>>>>>> TYPE;
	//typedef double TYPE;
	std::cerr << "type bits: " << sizeof(TYPE) * 8 << std::endl;
	auto freeze = new BhattacharyyaSequence<TYPE, ORDER>();
	auto sequence = new int[LENGTH];
	(*freeze)(sequence, 3, 10);
	std::cout << "static const int sequence[" << LENGTH << "] = { ";
	for (int i = 0; i < LENGTH; ++i)
		std::cout << sequence[i] << ", ";
	std::cout << "};" << std::endl;
	delete[] sequence;
	delete freeze;
	return 0;
}

