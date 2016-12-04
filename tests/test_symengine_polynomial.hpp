#include "gtest/gtest.h"
#include <iostream>
#include <chrono>

#include <symengine/polynomial.h>
#include <symengine/mul.h>
#include <symengine/pow.h>
#include <symengine/dict.h>

using SymEngine::UnivariatePolynomial;
using SymEngine::univariate_polynomial;
using SymEngine::Symbol;
using SymEngine::symbol;
using SymEngine::Pow;
using SymEngine::RCP;
using SymEngine::make_rcp;
using SymEngine::print_stack_on_segfault;
using SymEngine::map_uint_mpz;
using SymEngine::Basic;
using SymEngine::one;
using SymEngine::zero;
using SymEngine::integer;
using SymEngine::vec_basic_eq_perm;

TEST(symenginePolynomial, Constructor_of_UnivariatePolynomial)
{
	RCP<const Symbol> x  = symbol("x");
	RCP<const UnivariatePolynomial> P = univariate_polynomial(x, 2, {{0, 1}, {1, 2}, {2, 1}});
	EXPECT_TRUE(P->__str__() == "x**2 + 2*x + 1");

	RCP<const UnivariatePolynomial> Q = UnivariatePolynomial::create(x, {1, 0, 2, 1});
	EXPECT_TRUE(Q->__str__() == "x**3 + 2*x**2 + 1");
}

TEST(symenginePolynomial, Adding_two_UnivariatePolynomial)
{
	RCP<const Symbol> x  = symbol("x");
	map_uint_mpz adict_ = {{0, 1}, {1, 2}, {2, 1}};
	map_uint_mpz bdict_ = {{0, 2}, {1, 3}, {2, 4}};
	const UnivariatePolynomial a(x, 2, std::move(adict_));
	const UnivariatePolynomial b(x, 2, std::move(bdict_));

	RCP<const Basic> c = add_uni_poly(a, b);
	//std::cout<<c->__str__();
	EXPECT_TRUE(c->__str__() == "5*x**2 + 5*x + 3");
}

TEST(symenginePolynomial, Negative_of_a_UnivariatePolynomial)
{
	RCP<const Symbol> x  = symbol("x");
	map_uint_mpz adict_ = {{0, 1}, {1, 2}, {2, 1}};
	const UnivariatePolynomial a(x, 2, std::move(adict_));

	RCP<const UnivariatePolynomial> b = neg_uni_poly(a);
	//std::cout<<b->__str__()<<std::endl;
	EXPECT_TRUE(b->__str__() == "-x**2 - 2*x - 1");
}

TEST(symenginePolynomial, Subtracting_two_UnivariatePolynomial)
{
	RCP<const Symbol> x  = symbol("x");
	map_uint_mpz adict_ = {{0, 1}, {1, 2}, {2, 1}};
	map_uint_mpz bdict_ = {{0, 2}, {1, 3}, {2, 4}};
	const UnivariatePolynomial a(x, 2, std::move(adict_));
	const UnivariatePolynomial b(x, 2, std::move(bdict_));

	RCP<const Basic> c = sub_uni_poly(b, a);
	//std::cout<<c->__str__();
	EXPECT_TRUE(c->__str__() == "3*x**2 + x + 1");
}

TEST(symenginePolynomial, Multiplication_of_two_UnivariatePolynomial)
{
	RCP<const Symbol> x  = symbol("x");
	RCP<const UnivariatePolynomial> a = univariate_polynomial(x, 2, {{0, 1}, {1, 2}, {2, 1}});
	RCP<const UnivariatePolynomial> b = univariate_polynomial(x, 2, {{0, -1}, {1, -2}, {2, -1}});

	RCP<const UnivariatePolynomial> c = mul_uni_poly(a, a);
	//std::cout<<c->__str__();
	RCP<const UnivariatePolynomial> d = mul_uni_poly(a, b);
	//std::cout<<c->__str__();

	EXPECT_TRUE(c->__str__() == "x**4 + 4*x**3 + 6*x**2 + 4*x + 1");
	EXPECT_TRUE(d->__str__() == "-x**4 - 4*x**3 - 6*x**2 - 4*x - 1");
}

TEST(symenginePolynomial, UnivariatePolynomial_get_args)
{
	RCP<const Symbol> x  = symbol("x");
	RCP<const UnivariatePolynomial> a = univariate_polynomial(x, 2, {{0, 1}, {1, 2}, {2, 1}});

	EXPECT_TRUE(vec_basic_eq_perm(a->get_args(), {one, mul(integer(2), x), pow(x, integer(2))}));
	EXPECT_TRUE(!vec_basic_eq_perm(a->get_args(), {one, mul(integer(3), x), pow(x, integer(2))}));
}

TEST(symenginePolynomial, Evaluation_of_UnivariatePolynomial)
{
	RCP<const Symbol> x  = symbol("x");
	RCP<const UnivariatePolynomial> a = univariate_polynomial(x, 2, {{0, 1}, {1, 2}, {2, 1}});

	EXPECT_TRUE(a->eval(2) == 9);
	EXPECT_TRUE(a->eval_bit(3) == 81);
}

TEST(symenginePolynomial, Derivative_of_UnivariatePolynomial)
{
	RCP<const Symbol> x  = symbol("x");
	RCP<const Symbol> y  = symbol("y");
	RCP<const UnivariatePolynomial> a = univariate_polynomial(x, 2, {{0, 1}, {1, 2}, {2, 1}});

	EXPECT_TRUE(a->diff(x)->__str__() == "2*x + 2");
	//std::cout<<a->diff(x)->__str__()<<std::endl;
	EXPECT_TRUE(a->diff(y)->__str__() == "0");
	//std::cout<<a->diff(y)->__str__()<<std::endl;
}

TEST(symenginePolynomial, Bool_checks_specific_UnivariatePolynomial_cases)
{
	RCP<const Symbol> x  = symbol("x");
	RCP<const UnivariatePolynomial> z = univariate_polynomial(x, 0, {{0, 0}});
	RCP<const UnivariatePolynomial> o = univariate_polynomial(x, 0, {{0, 1}});
	RCP<const UnivariatePolynomial> mo = univariate_polynomial(x, 0, {{0, -1}});
	RCP<const UnivariatePolynomial> i = univariate_polynomial(x, 0, {{0, 6}});
	RCP<const UnivariatePolynomial> s = univariate_polynomial(x, 1, {{1, 1}});
	RCP<const UnivariatePolynomial> m1 = univariate_polynomial(x, 1, {{1, 6}});
	RCP<const UnivariatePolynomial> m2 = univariate_polynomial(x, 3, {{3, 5}});
	RCP<const UnivariatePolynomial> po = univariate_polynomial(x, 5, {{5, 1}});
	RCP<const UnivariatePolynomial> poly = univariate_polynomial(x, 2, {{0, 1}, {1, 2}, {2, 1}});

	EXPECT_TRUE((z->is_zero() && !z->is_one() && !z->is_minus_one() && z->is_integer() && !z->is_symbol() &&
			!z->is_mul() && !z->is_pow()));
	EXPECT_TRUE((!o->is_zero() && o->is_one() && !o->is_minus_one() && o->is_integer() && !o->is_symbol() &&
			!o->is_mul() && !o->is_pow()));
	EXPECT_TRUE((!mo->is_zero() && !mo->is_one() && mo->is_minus_one() && mo->is_integer() && !mo->is_symbol() &&
			!mo->is_mul() && !mo->is_pow()));
	EXPECT_TRUE((!i->is_zero() && !i->is_one() && !i->is_minus_one() && i->is_integer() && !i->is_symbol() &&
			!i->is_mul() && !i->is_pow()));
	EXPECT_TRUE((!s->is_zero() && !s->is_one() && !s->is_minus_one() && !s->is_integer() && s->is_symbol() &&
			!s->is_mul() && !s->is_pow()));
	EXPECT_TRUE((!m1->is_zero() && !m1->is_one() && !m1->is_minus_one() && !m1->is_integer() && !m1->is_symbol() &&
			m1->is_mul() && !m1->is_pow()));
	EXPECT_TRUE((!m2->is_zero() && !m2->is_one() && !m2->is_minus_one() && !m2->is_integer() && !m2->is_symbol() &&
			m2->is_mul() && !m2->is_pow()));
	EXPECT_TRUE((!po->is_zero() && !po->is_one() && !po->is_minus_one() && !po->is_integer() && !po->is_symbol() &&
			!po->is_mul() && po->is_pow()));
	EXPECT_TRUE((!poly->is_zero() && !poly->is_one() && !poly->is_minus_one() && !poly->is_integer() && !poly->is_symbol() &&
			!poly->is_mul() && !poly->is_pow()));
}

TEST(symenginePolynomial, Univariate_Polynomial_expand)
{
	RCP<const Symbol> x  = symbol("x");
	RCP<const UnivariatePolynomial> a = univariate_polynomial(x, 3, {{1, 1}, {2, 1}, {3, 1}});
	RCP<const Basic> b = make_rcp<const Pow>(a, integer(3));
	RCP<const Basic> c = expand(b);

	EXPECT_TRUE(b->__str__() == "(x**3 + x**2 + x)**3");
	//std::cout<<b->__str__()<<std::endl;
	EXPECT_TRUE(c->__str__() == "x**9 + 3*x**8 + 6*x**7 + 7*x**6 + 6*x**5 + 3*x**4 + x**3");
	//std::cout<<c->__str__()<<std::endl;
}
