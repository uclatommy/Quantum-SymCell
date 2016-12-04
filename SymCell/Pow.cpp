/*
 * Pow.cpp
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 13, 2015
 */

#include <SymCell/Pow.h>

namespace Quantum
{
namespace SymCell
{

void Pow::declare_params(CellSockets& p)
{
    p.declare<bool>("expand", "Expand the answer?", false);
}

void Pow::declare_io(const CellSockets& p, CellSockets& i, CellSockets& o)
{
    o.declare<RCP<const Basic>>("ans", "The symbolic result of exponentiation.");
    o["ans"]->str = SymBasic::default_str;
    i.declare<CellSocket::none>("base", "The a parameter in f(a,b) = a ^ b");
    i.declare<CellSocket::none>("exp", "The b parameter in f(a,b) = a ^ b");
    i["base"]->required(true);
    i["exp"]->required(true);
}

void Pow::configure(const CellSockets &p, const CellSockets &i,
        const CellSockets &o)
{
    SymBasic::configure(p, i, o);
    SymBasic::fn = [this, &i](RCP<const Basic> &ans)
    {
        ans = pow(var(i["base"]),var(i["exp"]));
        return OK;
    };
    o["ans"]->str = SymBasic::default_str;
}

ReturnCode Pow::process(const CellSockets &i, const CellSockets &o)
{
    ReturnCode result = SymBasic::process(i, o);
    if(result==OK)
    {
        o["ans"] << ans_;
        o["ans"]->str = [&o](){return o["ans"]->get<RCP<const Basic>>()->__str__();};
    }
    return result;
}

Pow::Pow()
{
    SymBasic::ans_ = integer(1);
}

}//namespace SymCell
}//namespace Quantum
