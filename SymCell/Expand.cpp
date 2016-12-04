/*
 * Expand.cpp
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 10, 2015
 */

#include <SymCell/Expand.h>

namespace Quantum {
namespace SymCell {

void Expand::declare_io(const CellSockets &p, CellSockets &i, CellSockets &o)
{
    i.declare<RCP<const Basic>>("f(x)", "The symbolic expression to expand.");
    i["f(x)"]->required(true);
    o.declare<RCP<const Basic>>("ans", "The resulting expanded expression.");
    o["ans"]->str = [](){return "<RCP<const Basic>>";};

}

ReturnCode Expand::process(const CellSockets &i, const CellSockets &o)
{
    o["ans"] << expand(i.get<RCP<const Basic>>("f(x)"));
    o["ans"]->str = [&o](){return o["ans"]->get<RCP<const Basic>>()->__str__();};
    return OK;
}

}//namespace SymCell
}//namespace Quantum
