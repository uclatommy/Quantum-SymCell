/*
 * Expand.h
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 10, 2015
 */

#ifndef SYMCELL_EXPAND_H_
#define SYMCELL_EXPAND_H_

#include <Engine/kernel.h>
#include <SymCell_Config.h>
#include <symengine/basic.h>
#include <symengine/symbol.h>
#include <symengine/integer.h>
#include <SymCell/Basic.h>
using SymEngine::Basic;
using SymEngine::RCP;
using SymEngine::Integer;
using SymEngine::integer;
using SymEngine::Symbol;
using SymEngine::symbol;

namespace Quantum {
namespace SymCell{

class Expand{
public:
    static void declare_io(const CellSockets&, CellSockets&, CellSockets&);
    ReturnCode process(const CellSockets&, const CellSockets&);
};

}//namespace SymCell
}//namespace Quantum

#endif /* SYMCELL_EXPAND_H_ */
