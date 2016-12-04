/*
 * Div.cpp
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 14, 2015
 */

#include <SymCell/Div.h>

namespace Quantum
{
namespace SymCell
{

void Div::declare_params(CellSockets& p)
{
    p.declare<bool>("expand", "Expand the answer?", false);
}

void Div::declare_io(const CellSockets& p, CellSockets& i, CellSockets& o)
{
    o.declare<RCP<const Basic>>("ans", "The result from division.");
    o["ans"]->str = SymBasic::default_str;
    i.declare<CellSocket::none>("numerator", "The a parameter in f(a,b) = a / b");
    i.declare<CellSocket::none>("denominator", "The b parameter in f(a,b) = a / b");
    i["numerator"]->required(true);
    i["denominator"]->required(true);
}

void Div::configure(const CellSockets &p, const CellSockets &i,
        const CellSockets &o)
{
    SymBasic::configure(p, i, o);
    SymBasic::fn = [this, &i](RCP<const Basic> &ans)
    {
        ans = div(var(i["numerator"]),var(i["denominator"]));
        return OK;
    };
    o["ans"]->str = SymBasic::default_str;
}

ReturnCode Div::process(const CellSockets &i, const CellSockets &o)
{
    ReturnCode result = SymBasic::process(i, o);
    if(result==OK)
    {
        o["ans"] << ans_;
        o["ans"]->str = [&o](){return o["ans"]->get<RCP<const Basic>>()->__str__();};
    }
    return result;
}

Div::Div()
{
    SymBasic::ans_ = integer(1);
}

}//namespace SymCell
}//namespace Quantum



