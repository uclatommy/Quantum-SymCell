//#include "catch.hpp"
#define SYMENGINE_CHECK_THROW(expression, exception) \
try \
{ \
expression; \
SYMENGINE_ERROR("expected exception not thrown");\
} \
catch(exception &) \
{ \
}

#include "gtest/gtest.h"
#include <chrono>

#include <symengine/ntheory.h>
#include <symengine/integer.h>
#include <symengine/rational.h>
#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/dict.h>

using SymEngine::Basic;
using SymEngine::Integer;
using SymEngine::Rational;
using SymEngine::print_stack_on_segfault;
using SymEngine::RCP;
using SymEngine::fibonacci;
using SymEngine::lucas;
using SymEngine::factorial;
using SymEngine::integer;
using SymEngine::is_a;
using SymEngine::map_integer_uint;
using SymEngine::rcp_dynamic_cast;
using SymEngine::rcp_static_cast;
using SymEngine::mod_inverse;
using SymEngine::mod;
using SymEngine::Number;
using SymEngine::bernoulli;
using SymEngine::crt;
using SymEngine::primitive_root;
using SymEngine::primitive_root_list;
using SymEngine::multiplicative_order;
using SymEngine::totient;
using SymEngine::carmichael;

TEST(symengineNtheory, test_gcd_lcm)
{
    RCP<const Integer> i2 = integer(2);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i4 = integer(4);
    RCP<const Integer> i6 = integer(6);
    RCP<const Integer> g = integer(2);
    RCP<const Integer> s = integer(2);
    RCP<const Integer> t = integer(3);

    EXPECT_TRUE(eq(*gcd(*i2, *i4), *integer(2)));
    EXPECT_TRUE(eq(*gcd(*i2, *i3), *integer(1)));
    EXPECT_TRUE(eq(*gcd(*i2, *i6), *integer(2)));
    EXPECT_TRUE(eq(*gcd(*i3, *i6), *integer(3)));

    EXPECT_TRUE(eq(*lcm(*i2, *i4), *integer(4)));
    EXPECT_TRUE(eq(*lcm(*i2, *i3), *integer(6)));
    EXPECT_TRUE(eq(*lcm(*i2, *i6), *integer(6)));
    EXPECT_TRUE(eq(*lcm(*i3, *i6), *integer(6)));

    gcd_ext(outArg(g), outArg(s), outArg(t), *i2, *i3);
    EXPECT_TRUE(eq(*g, *integer(1)));
    EXPECT_TRUE(eq(*g, *add(mul(i2, s), mul(i3, t)))); // check if g = i2*s + i3*t

    gcd_ext(outArg(g), outArg(s), outArg(t), *i3, *i6);
    EXPECT_TRUE(eq(*g, *integer(3)));
    EXPECT_TRUE(eq(*g, *add(mul(i3, s), mul(i6, t)))); // check if g = i3*s + i6*t
}

TEST(symengineNtheory, test_nextprime)
{
    RCP<const Integer> i1 = integer(1);
    RCP<const Integer> i5 = integer(5);
    RCP<const Integer> i6 = integer(6);

    EXPECT_TRUE(eq(*nextprime(*i1), *integer(2)));
    EXPECT_TRUE(eq(*nextprime(*i5), *integer(7)));
    EXPECT_TRUE(eq(*nextprime(*i6), *integer(7)));
}

TEST(symengineNtheory, test_probab_prime_p)
{
    RCP<const Integer> i1 = integer(1);
    RCP<const Integer> i5 = integer(5);
    RCP<const Integer> i6 = integer(6);

    EXPECT_TRUE(probab_prime_p(*i1) == 0);
    EXPECT_TRUE(probab_prime_p(*i5) == 2);
    EXPECT_TRUE(probab_prime_p(*i6) == 0);
}

TEST(symengineNtheory, test_modular_inverse)
{
    RCP<const Integer> i5 = integer(5);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i8 = integer(8);
    RCP<const Integer> i11 = integer(11);
    RCP<const Integer> b;

    EXPECT_TRUE(mod_inverse(outArg(b), *i3, *i5) != 0);
    EXPECT_TRUE(eq(*b, *integer(2)));

    EXPECT_TRUE(mod_inverse(outArg(b), *i3, *i8) != 0);
    EXPECT_TRUE(eq(*b, *integer(3)));

    EXPECT_TRUE(mod_inverse(outArg(b), *i3, *i11) != 0);
    EXPECT_TRUE(eq(*b, *integer(4)));
}

TEST(symengineNtheory, test_modulo)
{
    RCP<const Integer> i5 = integer(5);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i8 = integer(8);
    RCP<const Integer> i11 = integer(11);
    RCP<const Number> b;

    b = mod(*i5, *i3);
    EXPECT_TRUE(eq(*b, *integer(2)));

    b = mod(*i11, *i8);
    EXPECT_TRUE(eq(*b, *integer(3)));

    b = mod(*i11, *i3);
    EXPECT_TRUE(eq(*b, *integer(2)));
}

TEST(symengineNtheory, test_fibonacci_lucas)
{
    RCP<const Integer> g;
    RCP<const Integer> s;

    EXPECT_TRUE(eq(*fibonacci(1), *integer(1)));
    EXPECT_TRUE(eq(*fibonacci(2), *integer(1)));
    EXPECT_TRUE(eq(*fibonacci(3), *integer(2)));
    EXPECT_TRUE(eq(*fibonacci(5), *integer(5)));

    EXPECT_TRUE(eq(*lucas(1), *integer(1)));
    EXPECT_TRUE(eq(*lucas(2), *integer(3)));
    EXPECT_TRUE(eq(*lucas(3), *integer(4)));
    EXPECT_TRUE(eq(*lucas(5), *integer(11)));

    fibonacci2(outArg(g), outArg(s), 10);
    EXPECT_TRUE(eq(*g, *integer(55)));
    EXPECT_TRUE(eq(*s, *integer(34)));

    lucas2(outArg(g), outArg(s), 10);
    EXPECT_TRUE(eq(*g, *integer(123)));
    EXPECT_TRUE(eq(*s, *integer(76)));
}

TEST(symengineNtheory, test_binomial)
{
    RCP<const Integer> i10 = integer(10);
    RCP<const Integer> i5 = integer(5);
    RCP<const Integer> i0 = integer(0);
    RCP<const Integer> m10 = integer(-10);

    EXPECT_TRUE(eq(*binomial(*i10, 1), *i10));
    EXPECT_TRUE(eq(*binomial(*i5, 2), *i10));
    EXPECT_TRUE(eq(*binomial(*i5, 10), *i0));
    EXPECT_TRUE(eq(*binomial(*i10, 11), *i0));
    EXPECT_TRUE(eq(*binomial(*i10, 2), *integer(45)));

    EXPECT_TRUE(eq(*binomial(*m10, 3), *integer(-220)));
    EXPECT_TRUE(eq(*binomial(*m10, 2), *integer(55)));
}

TEST(symengineNtheory, test_factorial)
{
    RCP<const Integer> i1 = integer(1);

    EXPECT_TRUE(eq(*factorial(1), *i1));
    EXPECT_TRUE(eq(*factorial(0), *i1));
    EXPECT_TRUE(eq(*factorial(5), *integer(120)));
    EXPECT_TRUE(eq(*factorial(9), *integer(362880)));
}

TEST(symengineNtheory, test_factor)
{
    RCP<const Integer> i2 = integer(2);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i6 = integer(6);
    RCP<const Integer> i17 = integer(17);
    RCP<const Integer> i31 = integer(31);
    RCP<const Integer> i121 = integer(121);
    RCP<const Integer> i122 = integer(122);
    RCP<const Integer> i1001 = integer(1001);
    RCP<const Integer> i900 = integer(900);
    RCP<const Integer> f;

    EXPECT_TRUE(factor(outArg(f), *i2) == 0);
    EXPECT_TRUE(factor(outArg(f), *i3) == 0);
    EXPECT_TRUE(factor(outArg(f), *i17) == 0);
    EXPECT_TRUE(factor(outArg(f), *i31) == 0);

    EXPECT_TRUE(factor(outArg(f), *i6) > 0);
    EXPECT_TRUE(divides(*i6, *f));
    EXPECT_TRUE(factor(outArg(f), *i121) > 0);
    EXPECT_TRUE(divides(*i121, *f));
    EXPECT_TRUE(factor(outArg(f), *i122) > 0);
    EXPECT_TRUE(divides(*i122, *f));
    EXPECT_TRUE(factor(outArg(f), *i1001) > 0);
    EXPECT_TRUE(divides(*i1001, *f));
    EXPECT_TRUE(!divides(*i1001, *i6));
    EXPECT_TRUE(factor(outArg(f), *i900) > 0);
    EXPECT_TRUE(divides(*i900, *f));
}

TEST(symengineNtheory, test_factor_lehman_method)
{
    RCP<const Integer> i1 = integer(1);
    RCP<const Integer> i21 = integer(21);
    RCP<const Integer> i23 = integer(23);
    RCP<const Integer> i31 = integer(31);
    RCP<const Integer> i47 = integer(47);
    RCP<const Integer> i121 = integer(121);
    RCP<const Integer> i122 = integer(122);
    RCP<const Integer> i900 = integer(900);
    RCP<const Integer> i1001 = integer(1001);
    RCP<const Integer> f;

    EXPECT_TRUE(factor_lehman_method(outArg(f), *i23) == 0);
    EXPECT_TRUE(factor_lehman_method(outArg(f), *i31) == 0);
    EXPECT_TRUE(factor_lehman_method(outArg(f), *i47) == 0);

    EXPECT_TRUE(factor_lehman_method(outArg(f), *i21) > 0);
    EXPECT_TRUE((divides(*i21, *f) && !eq(*f, *i1) && !eq(*f, *i21)));   //Lehman's method returns only a proper divisor when composite
    EXPECT_TRUE(factor_lehman_method(outArg(f), *i121) > 0);
    EXPECT_TRUE((divides(*i121, *f) && !eq(*f, *i1) && !eq(*f, *i121)));
    EXPECT_TRUE(factor_lehman_method(outArg(f), *i122) > 0);
    EXPECT_TRUE((divides(*i122, *f) && !eq(*f, *i1) && !eq(*f, *i122)));
    EXPECT_TRUE(factor_lehman_method(outArg(f), *i900) > 0);
    EXPECT_TRUE((divides(*i900, *f) && !eq(*f, *i1) && !eq(*f, *i900)));
    EXPECT_TRUE(factor_lehman_method(outArg(f), *i1001) > 0);
    EXPECT_TRUE((divides(*i1001, *f) && !eq(*f, *i1) && !eq(*f, *i1001)));
}

TEST(symengineNtheory, test_factor_pollard_pm1_method)
{
    RCP<const Integer> i23 = integer(23);
    RCP<const Integer> i31 = integer(31);
    RCP<const Integer> i47 = integer(47);
    RCP<const Integer> i121 = integer(121);
    RCP<const Integer> i122 = integer(122);
    RCP<const Integer> i900 = integer(900);
    RCP<const Integer> i1001 = integer(1001);
    RCP<const Integer> i1850 = integer(1850);
    RCP<const Integer> f;

    EXPECT_TRUE(factor_pollard_pm1_method(outArg(f), *i23) == 0);
    EXPECT_TRUE(factor_pollard_pm1_method(outArg(f), *i31) == 0);
    EXPECT_TRUE(factor_pollard_pm1_method(outArg(f), *i47) == 0);

    EXPECT_TRUE((factor_pollard_pm1_method(outArg(f), *i121) == 0 || divides(*i121, *f)));
    EXPECT_TRUE((factor_pollard_pm1_method(outArg(f), *i122) == 0 || divides(*i122, *f)));
    EXPECT_TRUE((factor_pollard_pm1_method(outArg(f), *i900) == 0 || divides(*i900, *f)));
    EXPECT_TRUE((factor_pollard_pm1_method(outArg(f), *i1001, 20) == 0 || divides(*i1001, *f)));
    EXPECT_TRUE((factor_pollard_pm1_method(outArg(f), *i1850) == 0 || divides(*i1850, *f)));
}

TEST(symengineNtheory, test_factor_pollard_rho_method)
{
    RCP<const Integer> i23 = integer(23);
    RCP<const Integer> i31 = integer(31);
    RCP<const Integer> i47 = integer(47);
    RCP<const Integer> i121 = integer(121);
    RCP<const Integer> i122 = integer(122);
    RCP<const Integer> i900 = integer(900);
    RCP<const Integer> i1001 = integer(1001);
    RCP<const Integer> i1850 = integer(1850);
    RCP<const Integer> f;

    EXPECT_TRUE(factor_pollard_rho_method(outArg(f), *i23) == 0);
    EXPECT_TRUE(factor_pollard_rho_method(outArg(f), *i31) == 0);
    EXPECT_TRUE(factor_pollard_rho_method(outArg(f), *i47) == 0);

    EXPECT_TRUE((factor_pollard_rho_method(outArg(f), *i121) == 0 || divides(*i121, *f)));
    EXPECT_TRUE((factor_pollard_rho_method(outArg(f), *i122) == 0 || divides(*i122, *f)));
    EXPECT_TRUE((factor_pollard_rho_method(outArg(f), *i900) == 0 || divides(*i900, *f)));
    EXPECT_TRUE((factor_pollard_rho_method(outArg(f), *i1001) == 0 || divides(*i1001, *f)));
    EXPECT_TRUE((factor_pollard_rho_method(outArg(f), *i1850) == 0 || divides(*i1850, *f)));
}

TEST(symengineNtheory, test_sieve)
{
    const int MAX = 100003;
    std::vector<unsigned> v;
    //auto t1 = std::chrono::high_resolution_clock::now();
    SymEngine::Sieve::generate_primes(v, MAX);
    //auto t2 = std::chrono::high_resolution_clock::now();
    /*std::cout
        << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()
        << "us" << std::endl;
    std::cout << "Number of primes up to " << MAX << ": " << v.size() << std::endl;*/
    EXPECT_TRUE(v.size() == 9593);
}

TEST(symengineNtheory, test_sieve_iterator)
{
    const int MAX = 100003;
    int count = 0, prime;
    SymEngine::Sieve::iterator pi(MAX);
    //auto t1 = std::chrono::high_resolution_clock::now();
    while((prime=pi.next_prime()) <= MAX){
        count++;
    }
    //auto t2 = std::chrono::high_resolution_clock::now();
    /*std::cout
        << std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()
        << "us" << std::endl;
    std::cout << "Number of primes up to " << MAX << ": " << count << std::endl;*/
    EXPECT_TRUE(count == 9593);
}

// helper function for test_primefactors
void _test_primefactors(const RCP<const Integer> &a, unsigned size)
{
    std::vector<RCP<const Integer>> primes;

    prime_factors(primes, *a);
    EXPECT_TRUE(primes.size() == size);

    for (auto &it: primes) {
        EXPECT_TRUE(divides(*a, *it) == true);
        EXPECT_TRUE(probab_prime_p(*it) > 0);
    }
}

TEST(symengineNtheory, test_prime_factors)
{
    RCP<const Integer> i0 = integer(0);
    RCP<const Integer> i1 = integer(1);
    RCP<const Integer> i5 = integer(5);
    RCP<const Integer> i6 = integer(6);
    RCP<const Integer> i12 = integer(12);
    RCP<const Integer> i36 = integer(36);
    RCP<const Integer> i125 = integer(125);
    RCP<const Integer> i1001 = integer(1001);

    _test_primefactors(i0, 0);
    _test_primefactors(i1, 0);
    _test_primefactors(i5, 1);
    _test_primefactors(i6, 2);
    _test_primefactors(i12, 3);
    _test_primefactors(i36, 4);
    _test_primefactors(i125, 3);
    _test_primefactors(i1001, 3);
}

void _test_prime_factor_multiplicities(const RCP<const Integer> &a)
{
    unsigned multiplicity;
    RCP<const Integer> _a = a;
    map_integer_uint prime_mul;

    prime_factor_multiplicities(prime_mul, *a);

    for (auto it : prime_mul) {
        multiplicity = it.second;
        while(multiplicity) {
            _a = rcp_dynamic_cast<const Integer>(div(_a, it.first));
            multiplicity--;
        }
    }

    EXPECT_TRUE(eq(*_a, *integer(1)));
}

TEST(symengineNtheory, test_prime_factor_multiplicities)
{
    RCP<const Integer> i2 = integer(2);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i6 = integer(6);
    RCP<const Integer> i12 = integer(12);
    RCP<const Integer> i36 = integer(36);
    RCP<const Integer> i125 = integer(125);
    RCP<const Integer> i2357 = integer(2357);

    _test_prime_factor_multiplicities(i2);
    _test_prime_factor_multiplicities(i3);
    _test_prime_factor_multiplicities(i6);
    _test_prime_factor_multiplicities(i12);
    _test_prime_factor_multiplicities(i36);
    _test_prime_factor_multiplicities(i125);
    _test_prime_factor_multiplicities(i2357);
}

TEST(symengineNtheory, test_bernoulli)
{
    RCP<const Number> r1;
    RCP<const Number> r2;
    #ifdef HAVE_SYMENGINE_ARB
        r1 = bernoulli(12);
        r2 = Rational::from_two_ints(*integer(-691), *integer(2730));
        EXPECT_TRUE(eq(*r1, *r2));
    #else
        SYMENGINE_CHECK_THROW(bernoulli(12), std::runtime_error)
    #endif
}

TEST(symengineNtheory, test_crt)
{
    RCP<const Integer> g;
    std::vector<RCP<const Integer>> r, m;
    r = {integer(21), integer(31), integer(6), integer(17), integer(83)};
    m = {integer(30), integer(35), integer(45), integer(77), integer(88)};
    EXPECT_TRUE(crt(outArg(g), r, m) == true);
    EXPECT_TRUE(eq(*g, *integer(9411)));

    r = {integer(3), integer(2), integer(1)};
    m = {integer(20), integer(14), integer(11)};
    EXPECT_TRUE(crt(outArg(g), r, m) == false);

    r = {integer(3), integer(21), integer(23), integer(9), integer(45)};
    m = {integer(15), integer(48), integer(55), integer(61), integer(66)};
    EXPECT_TRUE(crt(outArg(g), r, m) == true);
    EXPECT_TRUE(eq(*g, *integer(12453)));

    r = {integer(-1), integer(-1), integer(-1), integer(-1), integer(-1)};
    m = {integer(2), integer(3), integer(4), integer(5), integer(6)};
    EXPECT_TRUE(crt(outArg(g), r, m) == true);
    EXPECT_TRUE(eq(*g, *integer(59)));
}

TEST(symengineNtheory, test_primitive_root)
{
    RCP<const Integer> i15 = integer(15);
    RCP<const Integer> im18 = integer(-18);
    RCP<const Integer> im22 = integer(-22);
    RCP<const Integer> i162 = integer(162);
    RCP<const Integer> i100 = integer(100);
    RCP<const Integer> i = integer(40487*40487);
    RCP<const Integer> g, p;

    EXPECT_TRUE(primitive_root(outArg(g), *i15) == false);
    EXPECT_TRUE(primitive_root(outArg(g), *i100) == false);

    EXPECT_TRUE(primitive_root(outArg(g), *im18) == true);
    EXPECT_TRUE(multiplicative_order(outArg(p), g, im18) == true );
    EXPECT_TRUE(eq(*p, *totient(im18)));

    EXPECT_TRUE(primitive_root(outArg(g), *i) == true);
    EXPECT_TRUE(multiplicative_order(outArg(p), g, i) == true );
    EXPECT_TRUE(eq(*p, *totient(i)));

    std::vector<RCP<const Integer>> roots, v;
    primitive_root_list(roots, *i162);
    EXPECT_TRUE(roots.size() == 18);

    roots.clear();
    primitive_root_list(roots, *i100);
    EXPECT_TRUE(roots.size() == 0);

    roots.clear();
    primitive_root_list(roots, *im22);
    EXPECT_TRUE(roots.size() == 4);
    v = {integer(7), integer(13), integer(17), integer(19)};
    bool same = std::equal(v.begin(), v.end(), roots.begin(),
            SymEngine::RCPBasicKeyEq());
    EXPECT_TRUE(same == true);
}

TEST(symengineNtheory, test_totient_carmichael)
{
    RCP<const Integer> i8 = integer(8);
    RCP<const Integer> i9 = integer(9);
    RCP<const Integer> i30 = integer(30);
    RCP<const Integer> im1729 = integer(-1729);

    EXPECT_TRUE(eq(*totient(i8), *integer(4)));
    EXPECT_TRUE(eq(*totient(i9), *integer(6)));
    EXPECT_TRUE(eq(*totient(i30), *integer(8)));
    EXPECT_TRUE(eq(*totient(im1729), *integer(1296)));

    EXPECT_TRUE(eq(*carmichael(i8), *integer(2)));
    EXPECT_TRUE(eq(*carmichael(i9), *integer(6)));
    EXPECT_TRUE(eq(*carmichael(i30), *integer(4)));
    EXPECT_TRUE(eq(*carmichael(im1729), *integer(36)));
}

TEST(symengineNtheory, test_multiplicative_order)
{
    RCP<const Integer> i0 = integer(0);
    RCP<const Integer> i1 = integer(1);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i2 = integer(2);
    RCP<const Integer> i6 = integer(6);
    RCP<const Integer> i9 = integer(9);
    RCP<const Integer> i13 = integer(13);
    RCP<const Integer> g;

    EXPECT_TRUE(multiplicative_order(outArg(g), i0, i9) == false);
    EXPECT_TRUE(multiplicative_order(outArg(g), i2, i6) == false);
    EXPECT_TRUE(multiplicative_order(outArg(g), i1, i13) == true);
    EXPECT_TRUE(eq(*g, *i1));
    EXPECT_TRUE(multiplicative_order(outArg(g), i13, i9) == true);
    EXPECT_TRUE(eq(*g, *i3));
    EXPECT_TRUE(multiplicative_order(outArg(g), i2, i9) == true);
    EXPECT_TRUE(eq(*g, *i6));
    EXPECT_TRUE(multiplicative_order(outArg(g), i3, i13) == true);
    EXPECT_TRUE(eq(*g, *i3));
}

TEST(symengineNtheory, test_legendre_jacobi_kronecker)
{
    RCP<const Integer> im1 = integer(-1);
    RCP<const Integer> i1 = integer(1);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i4 = integer(4);
    RCP<const Integer> i5 = integer(5);
    RCP<const Integer> i8 = integer(8);
    RCP<const Integer> i9 = integer(9);
    RCP<const Integer> i15 = integer(15);
    RCP<const Integer> i23 = integer(23);
    RCP<const Integer> i27 = integer(27);
    RCP<const Integer> i93 = integer(93);
    RCP<const Integer> i115 = integer(115);

    EXPECT_TRUE(legendre(*im1, *i23) == -1);
    EXPECT_TRUE(legendre(*im1, *i3) == -1);
    EXPECT_TRUE(legendre(*i3, *i3) == 0);
    EXPECT_TRUE(legendre(*i4, *i5) == 1);

    EXPECT_TRUE(jacobi(*im1, *i93) == 1);
    EXPECT_TRUE(jacobi(*i4, *i27) == 1);
    EXPECT_TRUE(jacobi(*i5, *i115) == 0);
    EXPECT_TRUE(jacobi(*i93, *i115) == -1);

    EXPECT_TRUE(kronecker(*i8, *i27) == -1);
    EXPECT_TRUE(kronecker(*i4, *i8) == 0);
    EXPECT_TRUE(kronecker(*i8, *i23) == 1);
}

TEST(symengineNtheory, test_nthroot_mod)
{
    RCP<const Integer> im1 = integer(-1);
    RCP<const Integer> i1 = integer(1);
    RCP<const Integer> i2 = integer(2);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i4 = integer(4);
    RCP<const Integer> i5 = integer(5);
    RCP<const Integer> i9 = integer(9);
    RCP<const Integer> i10 = integer(10);
    RCP<const Integer> i16 = integer(16);
    RCP<const Integer> i18 = integer(18);
    RCP<const Integer> i23 = integer(23);
    RCP<const Integer> i27 = integer(27);
    RCP<const Integer> i31 = integer(31);
    RCP<const Integer> i32 = integer(32);
    RCP<const Integer> i41 = integer(41);
    RCP<const Integer> i64 = integer(64);
    RCP<const Integer> i93 = integer(93);
    RCP<const Integer> i100 = integer(100);
    RCP<const Integer> i105 = integer(105);
    RCP<const Integer> nthroot, rem;
    std::vector<RCP<const Integer>> roots, v;

    EXPECT_TRUE(nthroot_mod(outArg(nthroot), im1, i2, i23) == false);
    EXPECT_TRUE(nthroot_mod(outArg(nthroot), im1, i2, i93) == false);
    EXPECT_TRUE(nthroot_mod(outArg(nthroot), i3, i2, i27) == false);
    EXPECT_TRUE(nthroot_mod(outArg(nthroot), i18, i2, i27) == false);
    EXPECT_TRUE(nthroot_mod(outArg(nthroot), i9, i4, i64) == false);
    EXPECT_TRUE(nthroot_mod(outArg(nthroot), im1, i2, i23) == false);
    EXPECT_TRUE(nthroot_mod(outArg(nthroot), i2, i3, i105) == false);

    EXPECT_TRUE(nthroot_mod(outArg(nthroot), i5, i1, i100) == true);
    EXPECT_TRUE(eq(*nthroot, *i5));

    EXPECT_TRUE(nthroot_mod(outArg(nthroot), im1, i2, i41) == true);
    rem = integer(nthroot->as_mpz() * nthroot->as_mpz() - im1->as_mpz());
    EXPECT_TRUE(divides(*rem, *i41));

    EXPECT_TRUE(nthroot_mod(outArg(nthroot), i31, i4, i41) == true);
    nthroot_mod(outArg(nthroot), i32, i10, i41);
    nthroot_mod_list(roots, i1, i10, i100);

    EXPECT_TRUE(nthroot_mod(outArg(nthroot), i4, i2, i64) == true);
    rem = integer(nthroot->as_mpz() * nthroot->as_mpz() - i4->as_mpz());
    EXPECT_TRUE(divides(*rem, *i64));

    EXPECT_TRUE(nthroot_mod(outArg(nthroot), i32, i10, i41) == true);
    rem = rcp_static_cast<const Integer>(nthroot->powint(*i10));
    rem = integer(rem->as_mpz() - i32->as_mpz());
    EXPECT_TRUE(divides(*rem, *i41));

    roots.clear();
    nthroot_mod_list(roots, i9, i2, i27);
    EXPECT_TRUE(roots.size() == 6);
    v = {integer(3), integer(6), integer(12), integer(15), integer(21), integer(24)};
    bool same = std::equal(v.begin(), v.end(), roots.begin(),
            SymEngine::RCPBasicKeyEq());
    EXPECT_TRUE(same == true);

    roots.clear();
    nthroot_mod_list(roots, i1, i18, i105);
    EXPECT_TRUE(roots.size() == 24);
}

TEST(symengineNtheory, test_powermod)
{
    RCP<const Integer> im1 = integer(-1);
    RCP<const Integer> i1 = integer(1);
    RCP<const Integer> i2 = integer(2);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i4 = integer(4);
    RCP<const Integer> i15 = integer(15);
    RCP<const Integer> i18 = integer(18);
    RCP<const Integer> i23 = integer(23);
    RCP<const Integer> i41 = integer(41);
    RCP<const Integer> i105 = integer(105);
    RCP<const Integer> r;
    std::vector<RCP<const Integer>> powms;

    EXPECT_TRUE(powermod(outArg(r), i2, im1, i4) == false);
    EXPECT_TRUE(powermod(outArg(r), i4, i3, i41) == true);
    EXPECT_TRUE(eq(*r, *i23));

    EXPECT_TRUE(powermod(outArg(r), i2, i23->divint(*i41), i41) == true);
    EXPECT_TRUE(eq(*r, *integer(8)));

    powermod_list(powms, i15, i1->divint(*i18), i105);
    EXPECT_TRUE(powms.size() == 6);
}
