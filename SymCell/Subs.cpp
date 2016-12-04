/*
 * Subs.cpp
 *
 * Copyright (c) Thomas Chen - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas Chen <tkchen@gmail.com>, August 2015
 *
 */

#include <SymCell/Subs.h>

namespace Quantum
{
namespace SymCell
{

void Subs::declare_params(CellSockets &p)
{
    p.declare<bool>("expand", "Expand the answer?", false);
}

void Subs::declare_io(const CellSockets& p, CellSockets& i, CellSockets& o)
{
    o.declare<RCP<const Basic>>("ans", "The resulting symbolic expression.");
    o["ans"]->str = SymBasic::default_str;
    i.declare<CellSocket::none>("f(x)", "An expression where the substitution takes place.");
    i.declare<CellSocket::none>("a", "The subexpression to be replaced.");
    i.declare<CellSocket::none>("b", "The expression to use as replacement.");
    i["f(x)"]->required(true);
    i["a"]->required(true);
    i["b"]->required(true);
}

void Subs::configure(const CellSockets &p, const CellSockets &i,
        const CellSockets &o)
{
    SymBasic::configure(p, i, o);
    SymBasic::fn = [this, &i](RCP<const Basic> &ans)
    {
        map_basic_basic d;
        d[var(i["a"])] = var(i["b"]);
        ans = var(i["f(x)"])->subs(d);
        return OK;
    };
    o["ans"]->str = SymBasic::default_str;
}

ReturnCode Subs::process(const CellSockets &i, const CellSockets &o)
{
    ReturnCode result = SymBasic::process(i, o);
    if(result==OK)
    {
        o["ans"] << ans_;
        o["ans"]->str = [&o](){return o["ans"]->get<RCP<const Basic>>()->__str__();};
    }
    return result;
}

Subs::Subs()
{
    SymBasic::ans_ = integer(0);
}

}//namespace SymCell
}//namespace Quantum
