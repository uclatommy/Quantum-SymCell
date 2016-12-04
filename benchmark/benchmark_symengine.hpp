#ifndef BENCHMARK_SYMENGINE_HPP_
#define BENCHMARK_SYMENGINE_HPP_
#include "gtest/gtest.h"

class BenchmarkSymEngine: public ::testing::Test
{
protected:
	const std::string timerString = "[0;33m[    TIMER ] [m";
};
#endif
