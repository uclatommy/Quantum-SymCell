/*
 * Base.h
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 9, 2015
 */

#ifndef SYMCELL_BASIC_H_
#define SYMCELL_BASIC_H_

#include <Engine/kernel.h>
#include <SymCell_Config.h>
#include <Engine/sockethandle.hpp>

#include <string>
#include <functional>

#include <symengine/basic.h>
#include <symengine/add.h>
#include <symengine/symbol.h>
#include <symengine/dict.h>
#include <symengine/integer.h>
#include <symengine/rational.h>
#include <symengine/complex.h>
#include <symengine/mul.h>
#include <symengine/pow.h>
#include <symengine/functions.h>
#include <symengine/visitor.h>
#include <symengine/eval_double.h>
#include <symengine/real_double.h>

using SymEngine::Basic;
using SymEngine::Add;
using SymEngine::Mul;
using SymEngine::Symbol;
using SymEngine::symbol;
using SymEngine::umap_basic_num;
using SymEngine::map_basic_basic;
using SymEngine::Integer;
using SymEngine::integer;
using SymEngine::Rational;
using SymEngine::one;
using SymEngine::zero;
using SymEngine::Number;
using SymEngine::pow;
using SymEngine::RCP;
using SymEngine::make_rcp;
using SymEngine::print_stack_on_segfault;
using SymEngine::Complex;
using SymEngine::has_symbol;
using SymEngine::is_a;
using SymEngine::rcp_static_cast;
using SymEngine::set_basic;
using SymEngine::free_symbols;
using SymEngine::function_symbol;
using SymEngine::RealDouble;
using SymEngine::real_double;
using SymEngine::div;
using SymEngine::sub;
using SymEngine::map_basic_basic;

namespace Quantum {
namespace SymCell {

class SymBasic
{
public:
    SymBasic();
    virtual ~SymBasic(){}
    void configure(const CellSockets&, const CellSockets&, const CellSockets&);
    ReturnCode process(const CellSockets&, const CellSockets&);
    virtual std::string return_msg() = 0;
    static const std::function<std::string(void)> default_str;
protected:
    RCP<const Basic> ans_;
    bool expand_;
    std::function<ReturnCode(RCP<const Basic>&)> fn;
    std::function<std::string()> ret_msg;
    RCP<const Basic> var(cellsocket_ptr);
};

}//namespace SymCell
}//namespace Quantum



#endif /* SYMCELL_BASIC_H_ */
