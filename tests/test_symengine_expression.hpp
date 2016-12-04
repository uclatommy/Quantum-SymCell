#include "gtest/gtest.h"
#include <iostream>
#include <chrono>

#include <symengine/expression.h>

using SymEngine::Expression;
using SymEngine::symbol;

TEST(symengineExpression, Constructors_of_Expression)
{
	EXPECT_NO_THROW(Expression e0 = symbol("x"));
}

TEST(symengineExpression, Printing_of_Expression)
{
	Expression e0 = symbol("x");
	std::ostringstream s;
	s << e0;
	EXPECT_EQ("x", s.str());
}

TEST(symengineExpression, Arithmetic_of_Expression)
{
	std::ostringstream s;
	Expression x = symbol("x"), y = symbol("y");
	auto z = x + y;
	s << z;
	EXPECT_EQ("x + y", s.str());
	s.str("");
	z += y;
	s << z;
	EXPECT_EQ("x + 2*y", s.str());
	EXPECT_TRUE(z == x + y + y);
	EXPECT_TRUE(z == x + 2 * y);
	s.str("");
	s << pow(z, z);
	EXPECT_EQ("(x + 2*y)**(x + 2*y)", s.str());
	s.str("");
	s << pow(z, 45);
	EXPECT_EQ("(x + 2*y)**45", s.str());
	/*
	auto t1 = std::chrono::high_resolution_clock::now();
	auto res = expand(pow(z, 45) * pow(z, 45));
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count()
		<< "ns" << std::endl;
	std::cout << res << std::endl;
	*/
}
