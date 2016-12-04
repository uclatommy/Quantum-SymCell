/*
 * Base.cpp
 *
 * Copyright (c) Thomas - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thomas <tkchen@gmail.com>, Oct 9, 2015
 */

#include <SymCell/Basic.h>

namespace Quantum {
namespace SymCell {

const std::function<std::string(void)> SymBasic::default_str = []()
    {return std::string("<RCP<const Basic>>");};

SymBasic::SymBasic():ans_(integer(0)),expand_(false)
{
    fn = [this](RCP<const Basic> &ans){
        ans = RCP<const Basic>(integer(0));
        ret_msg = [](){return std::string("SymBasic lambda fn is not defined!");};
        return UNKNOWN;
    };
    ret_msg = [](){return std::string("All clear...");};
}

void SymBasic::configure(const CellSockets &p, const CellSockets &i,
        const CellSockets &o)
{
    if(p.count("expand")>0){
        expand_ = p.get<bool>("expand");
    }
}

ReturnCode SymBasic::process(const CellSockets& i, const CellSockets& o)
{
    ReturnCode result;
    result = fn(ans_);
    if(expand_)
    {
        ans_ = expand(ans_);
    }
    return result;
}

std::string SymBasic::return_msg()
{
    return ret_msg();
}

RCP<const Basic> SymBasic::var(cellsocket_ptr c)
{
    RCP<const Basic> result;
    if(c->is_type<std::string>())
    {
        result = symbol(c->get<std::string>());
    }
    else if(c->is_type<int>())
    {
        result = integer(c->get<int>());
    }
    else if(c->is_type<RCP<const Basic>>())
    {
        result = c->get<RCP<const Basic>>();
    }
    else if(c->is_type<double>())
    {
        result = real_double(c->get<double>());
    }
    else
    {
        throw std::runtime_error("Unsupported SymCell type: " + c->type_name());
    }
    return result;
}
}//namespace SymCell
}//namespace Quantum


