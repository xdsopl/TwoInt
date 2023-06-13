/*
Testbench for unsigned integer doubler

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <random>
#include <cassert>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iomanip>
#include "two_int.hh"

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
	if (0) {
		typedef TwoInt<uint8_t> u16;
		for (int i = 0; i < 65536; ++i) {
			for (int j = 0; j < 65536; ++j) {
				uint16_t a = i * j;
				u16 b = u16(i) * u16(j);
				assert(a == *reinterpret_cast<uint16_t *>(&b));
			}
		}
	}
	if (0) {
		typedef TwoInt<uint8_t> u16;
		typedef TwoInt<u16> u32;
		for (int i = 0; i < 65536; ++i) {
			for (int j = 0; j < 65536; ++j) {
				uint32_t a = i * j;
				u32 b = mul(u16(i), u16(j));
				assert(a == *reinterpret_cast<uint32_t *>(&b));
			}
		}
	}
	if (0) {
		typedef TwoInt<TwoInt<uint8_t>> u32;
		typedef TwoInt<u32> u64;
		for (int i = 0; i < (1 << 17); ++i) {
			for (int j = 0; j < (1 << 17); ++j) {
				uint64_t a = uint64_t(i) * uint64_t(j);
				u64 b = mul(u32(i), u32(j));
				assert(a == *reinterpret_cast<uint64_t *>(&b));
			}
		}
	}
	if (0) {
		typedef TwoInt<uint32_t> u64;
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<uint64_t> distribution(0, std::numeric_limits<uint64_t>::max());
		auto rand = std::bind(distribution, engine);
		for (int i = 0; i < (1 << 20); ++i) {
			uint64_t x = rand(), y = rand();
			uint64_t a = x + y;
			u64 b = u64(x) + u64(y);
			assert(a == *reinterpret_cast<uint64_t *>(&b));
		}
	}
	if (0) {
		typedef TwoInt<uint32_t> u64;
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<uint64_t> distribution(0, std::numeric_limits<uint64_t>::max());
		auto rand = std::bind(distribution, engine);
		for (int i = 0; i < (1 << 20); ++i) {
			uint64_t x = rand(), y = rand();
			uint64_t a = x - y;
			u64 b = u64(x) - u64(y);
			assert(a == *reinterpret_cast<uint64_t *>(&b));
		}
	}
	if (0) {
		typedef TwoInt<uint16_t> u32;
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<uint32_t> distribution(0, std::numeric_limits<uint32_t>::max());
		auto rand = std::bind(distribution, engine);
		for (int i = 0; i < (1 << 20); ++i) {
			uint32_t x = rand(), y = rand();
			uint32_t a = x * y;
			u32 b = u32(x) * u32(y);
			assert(a == *reinterpret_cast<uint32_t *>(&b));
		}
	}
	if (0) {
		typedef TwoInt<uint16_t> u32;
		typedef TwoInt<u32> u64;
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<uint32_t> distribution(0, std::numeric_limits<uint32_t>::max());
		auto rand = std::bind(distribution, engine);
		for (int i = 0; i < (1 << 20); ++i) {
			uint64_t x = rand(), y = rand();
			uint64_t a = x * y;
			u64 b = mul(u32(x), u32(y));
			assert(a == *reinterpret_cast<uint64_t *>(&b));
		}
	}
	if (0) {
		typedef TwoInt<uint32_t> u64;
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<uint64_t> distribution(0, std::numeric_limits<uint64_t>::max());
		auto rand = std::bind(distribution, engine);
		for (int i = 0; i < (1 << 20); ++i) {
			uint64_t x = rand(), y = rand();
			uint64_t a = x * y;
			u64 b = u64(x) * u64(y);
			assert(a == *reinterpret_cast<uint64_t *>(&b));
		}
	}
	if (0) {
		typedef TwoInt<uint32_t> u64;
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<uint64_t> distribution(1, std::numeric_limits<uint64_t>::max());
		auto rand = std::bind(distribution, engine);
		for (int i = 0; i < (1 << 20); ++i) {
			uint64_t x = rand(), y = rand();
			uint64_t a = x / y;
			u64 b = u64(x) / u64(y);
			assert(a == *reinterpret_cast<uint64_t *>(&b));
		}
	}
	if (0) {
		typedef TwoInt<uint32_t> u64;
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<uint64_t> distribution(1, std::numeric_limits<uint64_t>::max());
		auto rand = std::bind(distribution, engine);
		for (int i = 0; i < (1 << 20); ++i) {
			uint64_t x = rand(), y = rand();
			uint64_t a = x % y;
			u64 b = u64(x) % u64(y);
			assert(a == *reinterpret_cast<uint64_t *>(&b));
		}
	}
	if (0) {
		typedef TwoInt<uint32_t> u64;
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<uint64_t> distribution(1, std::numeric_limits<uint64_t>::max());
		auto rand = std::bind(distribution, engine);
		for (int i = 0; i < (1 << 20); ++i) {
			uint64_t x = rand(), y = rand();
			uint64_t quotient = x / y;
			uint64_t remainder = x % y;
			TwoInt<u64> b = div(u64(x), u64(y));
			assert(quotient == *reinterpret_cast<uint64_t *>(&(b.lower)));
			assert(remainder == *reinterpret_cast<uint64_t *>(&(b.upper)));
		}
	}
	//TwoInt<TwoInt<TwoInt<TwoInt<uint8_t>>>> a(15), b(3);
	//TwoInt<TwoInt<uint8_t>> a(15), b(3);
	//TwoInt<TwoInt<TwoInt<uint32_t>>> a(15), b(3);
	TwoInt<uint32_t> a(15), b(3);
	std::cout << "sizeof(a) = " << sizeof(a) << std::endl;
	std::cout << "a.one() = " << a.one() << std::endl;
	std::cout << "a.max() = " << a.max() << std::endl;
	std::cout << (a + b) << " = " << a << " + " << b << std::endl;
	std::cout << (a - b) << " = " << a << " - " << b << std::endl;
	std::cout << (a * b) << " = " << a << " * " << b << std::endl;
	std::cout << (a / b) << " = " << a << " / " << b << std::endl;
	std::cout << (a % b) << " = " << a << " % " << b << std::endl;
	return 0;
}

