#include "gtest/gtest.h"
#include <iostream>
#include <chrono>

#include "Teuchos_stacktrace.hpp"

#include <symengine/basic.h>
#include <symengine/add.h>
#include <symengine/symbol.h>
#include <symengine/dict.h>
#include <symengine/integer.h>
#include <symengine/mul.h>
#include <symengine/pow.h>
#include "benchmark/benchmark_symengine.hpp"

using SymEngine::Basic;
using SymEngine::Add;
using SymEngine::Mul;
using SymEngine::Pow;
using SymEngine::Symbol;
using SymEngine::symbol;
using SymEngine::map_vec_int;
using SymEngine::integer;
using SymEngine::multinomial_coefficients;
using SymEngine::RCP;
using SymEngine::rcp_dynamic_cast;

TEST_F(BenchmarkSymEngine, add)
{
    Teuchos::print_stack_on_segfault();

    RCP<const Basic> x = symbol("x");
    RCP<const Basic> a, c;
    int N;

    N = 3000; a = x; c = integer(1);
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        a = add(a, mul(c, pow(x, integer(i))));
        c = mul(c, integer(-1));
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout<< timerString
    		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
            << "ms" << std::endl;
}
