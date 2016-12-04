//#include "catch.hpp"
#include "gtest/gtest.h"
#include <algorithm>

#include <symengine/diophantine.h>
#include <symengine/matrix.h>
#include <symengine/integer.h>

using SymEngine::print_stack_on_segfault;
using SymEngine::DenseMatrix;
using SymEngine::integer;
using SymEngine::homogeneous_lde;

bool vec_dense_matrix_eq_perm(const std::vector<DenseMatrix> &a,
    const std::vector<DenseMatrix> &b) {

    // Can't be equal if # of entries differ:
    if (a.size() != b.size()) return false;
    // Loop over elements in "a"
    for (size_t i = 0; i < a.size(); i++) {
        // Find the element a[i] in "b"
        bool found = false;
        for (size_t j = 0; j < a.size(); j++) {
            if (a[i] == b[j]) {
                found = true;
                break;
            }
        }
        // If not found, then a != b
        if (!found) return false;
    }
    // If all elements were found, then a == b
    return true;
}

TEST(symengineDiophantine, test_homogeneous_lde)
{
    std::vector<DenseMatrix> basis, true_basis;

    // First two tests are taken from the following paper:
    // Evelyne Contejean, Herve Devie. An Efficient Incremental Algorithm
    // for Solving Systems of Linear Diophantine Equations. Information and
    // computation, 113(1):143-172, August 1994.

    DenseMatrix A = DenseMatrix(2, 4, {
        integer(-1), integer(1), integer(2), integer(-3),
        integer(-1), integer(3), integer(-2), integer(-1)});
    homogeneous_lde(basis, A);
    true_basis = std::vector<DenseMatrix>{
        DenseMatrix(1, 4, {integer(0), integer(1), integer(1), integer(1)}),
        DenseMatrix(1, 4, {integer(4), integer(2), integer(1), integer(0)})
    };

    EXPECT_TRUE(vec_dense_matrix_eq_perm(basis, true_basis));

    basis.clear();
    A = DenseMatrix(1, 4, {integer(-1), integer(1), integer(2), integer(-3)});
    homogeneous_lde(basis, A);
    true_basis = std::vector<DenseMatrix>{
        DenseMatrix(1, 4, {integer(0), integer(0), integer(3), integer(2)}),
        DenseMatrix(1, 4, {integer(0), integer(1), integer(1), integer(1)}),
        DenseMatrix(1, 4, {integer(0), integer(3), integer(0), integer(1)}),
        DenseMatrix(1, 4, {integer(1), integer(0), integer(2), integer(1)}),
        DenseMatrix(1, 4, {integer(2), integer(0), integer(1), integer(0)}),
        DenseMatrix(1, 4, {integer(1), integer(1), integer(0), integer(0)})
    };

    EXPECT_TRUE(vec_dense_matrix_eq_perm(basis, true_basis));

    basis.clear();
    A = DenseMatrix(1, 2, {integer(2), integer(3)});
    homogeneous_lde(basis, A);
    true_basis = std::vector<DenseMatrix>{};

    EXPECT_TRUE(vec_dense_matrix_eq_perm(basis, true_basis));

    basis.clear();
    A = DenseMatrix(1, 2, {integer(2), integer(-3)});
    homogeneous_lde(basis, A);
    true_basis = std::vector<DenseMatrix>{
        DenseMatrix(1, 2, {integer(3), integer(2)})
    };

    EXPECT_TRUE(vec_dense_matrix_eq_perm(basis, true_basis));
}
