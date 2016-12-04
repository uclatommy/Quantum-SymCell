/*
 * Eq.h
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 11, 2015
 */

#ifndef SYMCELL_COMPARE_H_
#define SYMCELL_COMPARE_H_

#include <Engine/kernel.h>
#include <SymCell_Config.h>
#include <SymCell/Basic.h>

namespace Quantum {
namespace SymCell {

class QUANTUM_API Eq: SymBasic
{
public:
    static void declare_io(const CellSockets&, CellSockets&, CellSockets&);
    ReturnCode process(const CellSockets&, const CellSockets&);
    std::string return_msg(){return SymBasic::return_msg();}
};

class QUANTUM_API Neq: SymBasic
{
public:
    static void declare_io(const CellSockets&, CellSockets&, CellSockets&);
    ReturnCode process(const CellSockets&, const CellSockets&);
    std::string return_msg(){return SymBasic::return_msg();}
};

}//namespace SymCell
}//namespace Quantum

#endif /* SYMCELL_COMPARE_H_ */
