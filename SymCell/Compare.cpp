/*
 * Eq.cpp
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 11, 2015
 */
#include <SymCell/Compare.h>

namespace Quantum {
namespace SymCell {

void Eq::declare_io(const CellSockets &p, CellSockets &i, CellSockets &o)
{
    o.declare<bool>("ans", "The result of testing for equivalence.", false);
    o["ans"]->str = [](){return "<bool>";};
    i.declare<CellSocket::none>("a", "An expression to be used in comparison.");
    i.declare<CellSocket::none>("b", "An expression to be used in comparison.");
    i["a"]->required(true);
    i["b"]->required(true);
}

ReturnCode Eq::process(const CellSockets &i, const CellSockets &o)
{
    o["ans"] << eq(*var(i["a"]), *var(i["b"]));
    o["ans"]->str = [&o]()
    {
        if(o["ans"]->get<bool>())
        {
            return std::string("True");
        }
        else
        {
            return std::string("False");
        }
    };
    return OK;
}

void Neq::declare_io(const CellSockets &p, CellSockets &i, CellSockets &o)
{
    o.declare<bool>("ans", "The result of testing for non-equivalence.", false);
    o["ans"]->str = [](){return "<bool>";};
    i.declare<CellSocket::none>("a", "An expression to be used in comparison.");
    i.declare<CellSocket::none>("b", "An expression to be used in comparison.");
}

ReturnCode Neq::process(const CellSockets &i, const CellSockets &o)
{
    o["ans"] << neq(*var(i["a"]), *var(i["b"]));
    o["ans"]->str = [&o]()
    {
        if(o["ans"]->get<bool>())
        {
            return std::string("True");
        }
        else
        {
            return std::string("False");
        }
    };
    return OK;
}

}//namespace SymCell
}//namespace Quantum


