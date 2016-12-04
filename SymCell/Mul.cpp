/*
 * Mul.cpp
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 10, 2015
 */

#include <SymCell/Mul.h>

namespace Quantum
{
namespace SymCell
{

void Mul::declare_params(CellSockets& p)
{
    p.declare<bool>("expand", "Expand the answer?", false);
}

void Mul::declare_io(const CellSockets& p, CellSockets& i, CellSockets& o)
{
    o.declare<RCP<const Basic>>("ans", "The symbolic result of multiplication.");
    o["ans"]->str = SymBasic::default_str;
    i.declare<CellSocket::none>("a", "The a parameter in f(a,b) = a * b");
    i.declare<CellSocket::none>("b", "The b parameter in f(a,b) = a * b");
    i["a"]->required(true);
    i["b"]->required(true);
}

void Mul::configure(const CellSockets &p, const CellSockets &i,
        const CellSockets &o)
{
    SymBasic::configure(p, i, o);
    SymBasic::fn = [this, &i](RCP<const Basic> &ans)
    {
        ans = mul(var(i["a"]),var(i["b"]));
        return OK;
    };
    o["ans"]->str = SymBasic::default_str;
}

ReturnCode Mul::process(const CellSockets &i, const CellSockets &o)
{
    ReturnCode result = SymBasic::process(i, o);
    if(result==OK)
    {
        o["ans"] << ans_;
        o["ans"]->str = [&o](){return o["ans"]->get<RCP<const Basic>>()->__str__();};
    }
    return result;
}

Mul::Mul()
{
    SymBasic::ans_ = integer(1);
}

}//namespace SymCell
}//namespace Quantum
