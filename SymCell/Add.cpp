/*
 * Add.cpp
 *
 * Copyright (c) Thomas Chen - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas Chen <tkchen@gmail.com>, August 2015
 *
 */

#include <SymCell/Add.h>

namespace Quantum
{
namespace SymCell
{

void Add::declare_params(CellSockets &p)
{
    p.declare<bool>("expand", "Expand the answer?", false);
}

void Add::declare_io(const CellSockets& p, CellSockets& i, CellSockets& o)
{
    o.declare<RCP<const Basic>>("ans", "The result of evaluation.");
    o["ans"]->str = SymBasic::default_str;
    i.declare<CellSocket::none>("a", "The a parameter in f(a,b) = a + b");
    i.declare<CellSocket::none>("b", "The b parameter in f(a,b) = a + b");
    i["a"]->required(true);
    i["b"]->required(true);
}

void Add::configure(const CellSockets &p, const CellSockets &i,
        const CellSockets &o)
{
    SymBasic::configure(p, i, o);
    SymBasic::fn = [this, &i](RCP<const Basic> &ans)
    {
        ans = add(var(i["a"]),var(i["b"]));
        return OK;
    };
    o["ans"]->str = SymBasic::default_str;
}

ReturnCode Add::process(const CellSockets &i, const CellSockets &o)
{
    ReturnCode result = SymBasic::process(i, o);
    if(result==OK)
    {
        o["ans"] << ans_;
        o["ans"]->str = [&o](){return o["ans"]->get<RCP<const Basic>>()->__str__();};
    }
    return result;
}

Add::Add()
{
    SymBasic::ans_ = integer(0);
}

}//namespace SymCell
}//namespace Quantum
