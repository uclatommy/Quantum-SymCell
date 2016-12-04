/*
 * SymCell.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: Thomas
 */
#include <SymCell.h>
//#include "gtest/gtest.h"
#include <SymCell/Expand.h>
#include <SymCell/Add.h>
#include <SymCell/Compare.h>
#include <SymCell/Mul.h>
#include <SymCell/Pow.h>
#include <SymCell/Div.h>
#include <SymCell/Sub.h>
#include <SymCell/Subs.h>

extern "C" SYMCELL_API int getEngineVersion()
{
    return 1;
}

extern "C" SYMCELL_API void registerPlugin(Quantum::Kernel &kernel)
{
    using namespace Quantum;
    std::vector<cell_ptr> cells_to_add;

    Cell_<SymCell::Add>::SHORT_DOC = "Defines the expression f(a,b) = a + b";
    Cell_<SymCell::Add>::MODULE_NAME = "SymCell";
    Cell_<SymCell::Add>::CELL_NAME = "Add";
    cells_to_add.push_back(std::shared_ptr<Cell>(new Cell_<SymCell::Add>()));
    cells_to_add[0]->categories.push_back("Math");
    cells_to_add[0]->categories.push_back("Symbolic");

    Cell_<SymCell::Mul>::SHORT_DOC = "Defines the expression f(a,b) = a * b";
    Cell_<SymCell::Mul>::MODULE_NAME = "SymCell";
    Cell_<SymCell::Mul>::CELL_NAME = "Mul";
    cells_to_add.push_back(std::shared_ptr<Cell>(new Cell_<SymCell::Mul>()));
    cells_to_add[1]->categories.push_back("Math");
    cells_to_add[1]->categories.push_back("Symbolic");

    Cell_<SymCell::Expand>::SHORT_DOC = "Expands a symbolic expression.";
    Cell_<SymCell::Expand>::MODULE_NAME = "SymCell";
    Cell_<SymCell::Expand>::CELL_NAME = "Expand";
    cells_to_add.push_back(std::shared_ptr<Cell>(new Cell_<SymCell::Expand>()));
    cells_to_add[2]->categories.push_back("Math");
    cells_to_add[2]->categories.push_back("Symbolic");

    Cell_<SymCell::Eq>::SHORT_DOC =
            "Determines if two symbolic expressions are equivalent.";
    Cell_<SymCell::Eq>::MODULE_NAME = "SymCell";
    Cell_<SymCell::Eq>::CELL_NAME = "Eq";
    cells_to_add.push_back(std::shared_ptr<Cell>(new Cell_<SymCell::Eq>()));
    cells_to_add[3]->categories.push_back("Math");
    cells_to_add[3]->categories.push_back("Symbolic");

    Cell_<SymCell::Pow>::SHORT_DOC = "Defines the expression f(a,b) = a ^ b";
    Cell_<SymCell::Pow>::MODULE_NAME = "SymCell";
    Cell_<SymCell::Pow>::CELL_NAME = "Pow";
    cells_to_add.push_back(std::shared_ptr<Cell>(new Cell_<SymCell::Pow>()));
    cells_to_add[4]->categories.push_back("Math");
    cells_to_add[4]->categories.push_back("Symbolic");

    Cell_<SymCell::Div>::SHORT_DOC = "Defines the expression f(a,b) = a / b";
    Cell_<SymCell::Div>::MODULE_NAME = "SymCell";
    Cell_<SymCell::Div>::CELL_NAME = "Div";
    cells_to_add.push_back(std::shared_ptr<Cell>(new Cell_<SymCell::Div>()));
    cells_to_add[5]->categories.push_back("Math");
    cells_to_add[5]->categories.push_back("Symbolic");

    Cell_<SymCell::Sub>::SHORT_DOC = "Defines the expression f(a,b) = a - b";
    Cell_<SymCell::Sub>::MODULE_NAME = "SymCell";
    Cell_<SymCell::Sub>::CELL_NAME = "Sub";
    cells_to_add.push_back(std::shared_ptr<Cell>(new Cell_<SymCell::Sub>()));
    cells_to_add[6]->categories.push_back("Math");
    cells_to_add[6]->categories.push_back("Symbolic");

    Cell_<SymCell::Sub>::SHORT_DOC =
            "Substitutes one subexpression for another.";
    Cell_<SymCell::Sub>::MODULE_NAME = "SymCell";
    Cell_<SymCell::Sub>::CELL_NAME = "Subs";
    cells_to_add.push_back(std::shared_ptr<Cell>(new Cell_<SymCell::Subs>()));
    cells_to_add[7]->categories.push_back("Math");
    cells_to_add[7]->categories.push_back("Symbolic");

    for(cell_ptr c: cells_to_add)
    {
        c->declare_params();
        c->declare_io();
        c->init();
        kernel.getCellRegistry().addCell(c, c->name());
    }

    //setup gtest parameters
    int argc = 2;
    char file[] = "dummy.dylib"; //this doesn't do anything
    char arg[] = "--gtest_color=true";
    char* option[2] = {file, arg};
    ::testing::InitGoogleTest(&argc, option);
    RUN_ALL_TESTS();
}
