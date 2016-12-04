//#include "catch.hpp"
#include "gtest/gtest.h"

#include <symengine/symengine_rcp.h>

using SymEngine::RCP;
using SymEngine::make_rcp;
using SymEngine::Ptr;
using SymEngine::null;
using SymEngine::EnableRCPFromThis;

// This is the canonical use of EnableRCPFromThis:

class Mesh : public EnableRCPFromThis<Mesh> {
public:
    int x, y;
};

TEST(symengineRCP, make_rcp)
{
    RCP<Mesh> m = make_rcp<Mesh>();
    Ptr<Mesh> p = m.ptr();
    EXPECT_TRUE(!(m == null));
    EXPECT_TRUE(p->use_count() == 1);
    RCP<Mesh> m2 = m;
    EXPECT_TRUE(p->use_count() == 2);
    RCP<Mesh> m3 = m2;
    EXPECT_TRUE(p->use_count() == 3);
}

void f(Mesh &m)
{
    EXPECT_TRUE(m.use_count() == 1);
    // rcp_from_this() gives up non const version of RCP<Mesh> because 'm' is
    // not const
    RCP<Mesh> m2 = m.rcp_from_this();
    EXPECT_TRUE(m.use_count() == 2);
    m2->x = 6;
}

void f_const(const Mesh &m)
{
    EXPECT_TRUE(m.use_count() == 1);
    // rcp_from_this() gives up const version of RCP<Mesh> because 'm' is const
    RCP<const Mesh> m2 = m.rcp_from_this();
    EXPECT_TRUE(m.use_count() == 2);
}

TEST(symengineRCP, rcp_from_this)
{
    RCP<Mesh> m = make_rcp<Mesh>();
    EXPECT_TRUE(m->use_count() == 1);
    m->x = 5;
    EXPECT_TRUE(m->x == 5);
    f(*m);
    EXPECT_TRUE(m->use_count() == 1);
    EXPECT_TRUE(m->x == 6);

    f_const(*m);
    EXPECT_TRUE(m->use_count() == 1);
}

TEST(symengineRCP, rcp_from_this_const)
{
    RCP<const Mesh> m = make_rcp<const Mesh>();
    EXPECT_TRUE(m->use_count() == 1);
    f_const(*m);
    EXPECT_TRUE(m->use_count() == 1);
}

// This is not a canonical way how to use EnableRCPFromThis, since we use
// 'const Mesh2' for the internal weak pointer, so we can only get
// 'RCP<const Mesh2>' out of rcp_from_this(). But it is legitimate code, so we
// test it as well.

class Mesh2 : public EnableRCPFromThis<const Mesh2> {
public:
    int x, y;
};

void f2_const(const Mesh2 &m)
{
    EXPECT_TRUE(m.use_count() == 1);
    // rcp_from_this() gives up const version of RCP<Mesh> because 'm' is const
    RCP<const Mesh2> m2 = m.rcp_from_this();
    EXPECT_TRUE(m.use_count() == 2);
}

void f2_hybrid(Mesh2 &m)
{
    EXPECT_TRUE(m.use_count() == 1);
    // rcp_from_this() gives up const version of RCP<Mesh> even though 'm' is
    // not const, because the internal pointer inside Mesh2 is const.
    RCP<const Mesh2> m2 = m.rcp_from_this();
    EXPECT_TRUE(m.use_count() == 2);
}

TEST(symengineRCP, rcp_from_this_const_2)
{
    RCP<const Mesh2> m = make_rcp<const Mesh2>();
    EXPECT_TRUE(m->use_count() == 1);
    f2_const(*m);
    EXPECT_TRUE(m->use_count() == 1);

    RCP<Mesh2> m2 = make_rcp<Mesh2>();
    EXPECT_TRUE(m2->use_count() == 1);
    f2_const(*m2);
    EXPECT_TRUE(m2->use_count() == 1);
    f2_hybrid(*m2);
    EXPECT_TRUE(m2->use_count() == 1);
}
