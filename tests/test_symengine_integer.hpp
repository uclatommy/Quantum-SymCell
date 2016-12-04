#include "gtest/gtest.h"

#include <symengine/integer.h>

using SymEngine::print_stack_on_segfault;
using SymEngine::RCP;
using SymEngine::Integer;
using SymEngine::integer;
using SymEngine::isqrt;

TEST(symengineInteger, isqrt)
{
	RCP<const Integer> i10 = integer(10);
	RCP<const Integer> i19 = integer(19);
	RCP<const Integer> i25 = integer(25);

	EXPECT_TRUE(eq(*isqrt(*i10), *integer(3)));
	EXPECT_TRUE(eq(*isqrt(*i19), *integer(4)));
	EXPECT_TRUE(eq(*isqrt(*i25), *integer(5)));
}

TEST(symengineInteger, i_nth_root)
{
	RCP<const Integer> i7 = integer(7);
	RCP<const Integer> i9 = integer(9);
	RCP<const Integer> i10 = integer(10);
	RCP<const Integer> r;

	EXPECT_TRUE(i_nth_root(outArg(r), *i7, 2) == 0);
	EXPECT_TRUE(eq(*r, *integer(2)));

	EXPECT_TRUE(i_nth_root(outArg(r), *i9, 2) != 0);
	EXPECT_TRUE(eq(*r, *integer(3)));

	EXPECT_TRUE(i_nth_root(outArg(r), *i9, 3) == 0);
	EXPECT_TRUE(eq(*r, *integer(2)));

	EXPECT_TRUE(i_nth_root(outArg(r), *i10, 2) == 0);
	EXPECT_TRUE(eq(*r, *integer(3)));
}

TEST(symengineInteger, perfect_power_square)
{
	RCP<const Integer> i7 = integer(7);
	RCP<const Integer> i8 = integer(8);
	RCP<const Integer> i9 = integer(9);
	RCP<const Integer> i10 = integer(10);

	EXPECT_TRUE(perfect_square(*i7) == 0);
	EXPECT_TRUE(perfect_power(*i7) == 0);
	EXPECT_TRUE(perfect_square(*i8) == 0);
	EXPECT_TRUE(perfect_power(*i8) != 0);
	EXPECT_TRUE(perfect_square(*i9) != 0);
	EXPECT_TRUE(perfect_power(*i9) != 0);
	EXPECT_TRUE(perfect_square(*i10) == 0);
	EXPECT_TRUE(perfect_power(*i10) == 0);
}

TEST(symengineInteger, iabs)
{
	RCP<const Integer> _i5 = integer(-5);
	RCP<const Integer> _i9 = integer(-9);
	RCP<const Integer> i12 =  integer(12);

	EXPECT_TRUE(eq(*iabs(*_i5), *integer(5)));
	EXPECT_TRUE(eq(*iabs(*_i9), *integer(9)));
	EXPECT_TRUE(eq(*iabs(*i12), *integer(12)));
}
