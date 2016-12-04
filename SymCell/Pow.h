/*
 * Pow.h
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 13, 2015
 */

#ifndef SYMCELL_POW_H_
#define SYMCELL_POW_H_

#include <Engine/kernel.h>
#include <SymCell_Config.h>
#include <SymCell/Basic.h>

namespace Quantum {
namespace SymCell {

class SYMCELL_API Pow: SymBasic
{
public:
    Pow();
    static void declare_params(CellSockets&);
    static void declare_io(const CellSockets&, CellSockets&, CellSockets&);
    void configure(const CellSockets&, const CellSockets&, const CellSockets&);
    ReturnCode process(const CellSockets&, const CellSockets&);
    std::string return_msg(){return SymBasic::return_msg();}
};

}//namespace SymCell
}//namespace Quantum





#endif /* SYMCELL_POW_H_ */
