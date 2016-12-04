/*
 * Add.h
 *
 * Copyright (c) Thomas Chen - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas Chen <tkchen@gmail.com>, August 2015
 */

#ifndef SYMCELL_ADD_H_
#define SYMCELL_ADD_H_

#include <Engine/kernel.h>
#include <SymCell_Config.h>
#include <SymCell/Basic.h>

namespace Quantum {
namespace SymCell {

class SYMCELL_API Add: SymBasic
{
public:
    Add();
    static void declare_params(CellSockets&);
    static void declare_io(const CellSockets&, CellSockets&, CellSockets&);
    void configure(const CellSockets&, const CellSockets&, const CellSockets&);
    ReturnCode process(const CellSockets&, const CellSockets&);
    std::string return_msg(){return SymBasic::return_msg();}
};

}//namespace SymCell
}//namespace Quantum

#endif /* SYMCELL_ADD_H_ */
