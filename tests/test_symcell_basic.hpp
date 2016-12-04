/*
 * test_symcell_basic.hpp
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 11, 2015
 */

#ifndef TESTS_TEST_SYMCELL_BASIC_HPP_
#define TESTS_TEST_SYMCELL_BASIC_HPP_

#include "Engine/cellregistry.h"
#include <memory>
/*
#include "Engine/omp_Scheduler.hpp"
#include "Engine/all.hpp"
*/
#include "SymCell/Add.h"
#include "SymCell/Mul.h"
#include "SymCell/Pow.h"
#include "SymCell/Div.h"
#include "SymCell/Compare.h"

#include <gtest/gtest.h>

namespace Quantum{
class SymCellTester : public ::testing::Test
{
public:
    void reset(std::shared_ptr<Cell> c)
    {
        c->declare_params();
        c->declare_io();
        c->configure();
    }
};

TEST_F(SymCellTester, Add_Mul)
{
    cell_ptr r1 = std::make_shared<Cell_<SymCell::Add>>();
    reset(r1);
    r1->inputs["a"] << std::string("x");
    r1->inputs["b"] << std::string("x");
    r1->process();
    EXPECT_TRUE("2*x" == r1->outputs["ans"]->str());

    cell_ptr r2 = std::make_shared<Cell_<SymCell::Mul>>();
    reset(r2);
    r2->inputs["a"] << 2;
    r2->inputs["b"] << std::string("x");
    r2->process();
    EXPECT_TRUE("2*x" == r2->outputs["ans"]->str());

    cell_ptr eq = std::make_shared<Cell_<SymCell::Eq>>();
    reset(eq);
    r1->outputs["ans"] >> eq->inputs["a"];
    r2->outputs["ans"] >> eq->inputs["b"];
    eq->process();
    EXPECT_TRUE(eq->outputs.get<bool>("ans"));

    //auto r3 = r2->clone(); //TODO: calling clone() from plugin causes segfault
    cell_ptr r3 = std::make_shared<Cell_<SymCell::Mul>>();
    reset(r3);
    r3->inputs["a"] << 3;
    r3->inputs["b"] << std::string("x");
    r3->process();
    eq = std::make_shared<Cell_<SymCell::Eq>>();
    reset(eq);
    r3->outputs["ans"] >> eq->inputs["a"];
    r1->outputs["ans"] >> eq->inputs["b"];
    eq->process();
    EXPECT_TRUE(!eq->outputs.get<bool>("ans"));

    cell_ptr neq = std::make_shared<Cell_<SymCell::Neq>>();
    reset(neq);
    r3->outputs["ans"] >> neq->inputs["a"];
    r1->outputs["ans"] >> neq->inputs["b"];
    neq->process();
    EXPECT_TRUE(neq->outputs.get<bool>("ans"));

    r3 = std::make_shared<Cell_<SymCell::Mul>>();
    reset(r3);
    r3->inputs["a"] << 2;
    r3->inputs["b"] << std::string("y");
    r3->process();
    neq = std::make_shared<Cell_<SymCell::Neq>>();
    reset(neq);
    r1->outputs["ans"] >> neq->inputs["a"];
    r3->outputs["ans"] >> neq->inputs["b"];
    neq->process();
    EXPECT_TRUE(neq->outputs.get<bool>("ans"));

    neq = std::make_shared<Cell_<SymCell::Neq>>();
    reset(neq);
    r2->outputs["ans"] >> neq->inputs["a"];
    r3->outputs["ans"] >> neq->inputs["b"];
    neq->process();
    EXPECT_TRUE(neq->outputs.get<bool>("ans"));
}

TEST_F(SymCellTester, Pow)
{
    cell_ptr add1 = std::make_shared<Cell_<SymCell::Add>>();
    reset(add1);
    cell_ptr pow1 = std::make_shared<Cell_<SymCell::Pow>>();
    reset(pow1);
    pow1->inputs["base"] << std::string("x");
    pow1->inputs["exp"] << std::string("y");
    pow1->process();
    pow1->outputs["ans"] >> add1->inputs["a"];
    add1->inputs["b"] << std::string("z");
    add1->process();
    cell_ptr add2 = std::make_shared<Cell_<SymCell::Add>>();
    reset(add2);
    add2->inputs["a"] << std::string("z");
    pow1->outputs["ans"] >> add2->inputs["b"];
    add2->process();
    cell_ptr eq = std::make_shared<Cell_<SymCell::Eq>>();
    reset(eq);
    add1->outputs["ans"] >> eq->inputs["a"];
    add2->outputs["ans"] >> eq->inputs["b"];
    eq->process();
    EXPECT_TRUE(eq->outputs.get<bool>("ans"));
}
TEST_F(SymCellTester, Div)
{
    cell_ptr r1 = std::make_shared<Cell_<SymCell::Div>>();
    reset(r1);
    r1->inputs["numerator"] << 1;
    r1->inputs["denominator"] << 2;
    r1->process();
    cell_ptr r2 = std::make_shared<Cell_<SymCell::Mul>>();
    reset(r2);
    r2->inputs["a"] << std::string("x");
    r2->inputs["b"] << 2;
    r2->process();
    cell_ptr r3 = std::make_shared<Cell_<SymCell::Div>>();
    reset(r3);
    r3->inputs["numerator"] << std::string("x");
    r2->outputs["ans"] >> r3->inputs["denominator"];
    r3->process();
    cell_ptr eq = std::make_shared<Cell_<SymCell::Eq>>();
    reset(eq);
    r1->outputs["ans"] >> eq->inputs["a"];
    r3->outputs["ans"] >> eq->inputs["b"];
    eq->process();
    EXPECT_TRUE(eq->outputs.get<bool>("ans"));
}

TEST_F(SymCellTester, Process_inputs_supplied)
{
    cell_ptr r1 = std::make_shared<Cell_<SymCell::Div>>();
    reset(r1);
    r1->inputs["numerator"] << 1;
    r1->inputs["denominator"] << 2;
    EXPECT_EQ(r1->process(0), Quantum::OK);
    cell_ptr r2 = std::make_shared<Cell_<SymCell::Mul>>();
    reset(r2);
    r2->inputs["a"] << std::string("x");
    r2->inputs["b"] << 2;
    EXPECT_EQ(r2->process(10), Quantum::OK);
    cell_ptr r3 = std::make_shared<Cell_<SymCell::Div>>();
    reset(r3);
    r3->inputs["numerator"] << std::string("x");
    r2->outputs["ans"] >> r3->inputs["denominator"];
    EXPECT_EQ(r3->process(3), Quantum::DO_OVER); //because r2 is at 10
    EXPECT_EQ(r3->process(10), Quantum::OK);
    cell_ptr eq = std::make_shared<Cell_<SymCell::Eq>>();
    reset(eq);
    r1->outputs["ans"] >> eq->inputs["a"];
    r3->outputs["ans"] >> eq->inputs["b"];
    EXPECT_EQ(eq->process(100), Quantum::DO_OVER);
    EXPECT_EQ(r1->process(10), Quantum::OK);
    r1->outputs["ans"] >> eq->inputs["a"];
    EXPECT_EQ(10, r3->outputs["ans"]->token_id());
    EXPECT_EQ(10, eq->inputs["b"]->token_id());
    EXPECT_EQ(eq->process(10), Quantum::OK);
    EXPECT_TRUE(eq->outputs.get<bool>("ans"));
}
/*
TEST_F(SymCellTester, Scheduling_symcells)
{
    cell_ptr r1 = std::make_shared<Cell_<SymCell::Div>>();
    reset(r1);
    r1->inputs["numerator"] << 1;
    r1->inputs["denominator"] << 2;
    cell_ptr r2 = std::make_shared<Cell_<SymCell::Mul>>();
    reset(r2);
    r2->inputs["a"] << std::string("x");
    circuit_ptr c(new Circuit);
    c->insert(r1);
    c->insert(r2);
    c->connect(r1, "ans", r2, "b");
    Scheduler s(c);
    EXPECT_TRUE(s.execute(10));
    EXPECT_EQ("1/2*x", r2->outputs["ans"]->str());
}
*/
}//namespace Quantum
#endif /* TESTS_TEST_SYMCELL_BASIC_HPP_ */
