
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include <unistd.h>

#include "bhtools.h"

struct test_a1 : public bhtools::Twork_base<int>
{
    bool process(int val) override
    {
        if (val == 1)
        {
            vlogd($(val));
            return true;
        }
        return false;
    }
};
struct test_a2 : public bhtools::Twork_base<int>
{
    bool process(int val) override
    {
        if (val == 12)
        {
            vlogd($(val));
            return true;
        }
        return false;
    }
};
struct test_a3 : public bhtools::Twork_base<int>
{
    bool process(int val) override
    {
        if (val == 123)
        {
            vlogd($(val));
            return true;
        }
        return false;
    }
};

struct test_base_b
{
    struct data
    {
        int a;
        int b;
        std::shared_ptr<int> ret;
        std::string flg;
    };
    virtual bool process(data d) = 0;
};

struct test_b1 : public test_base_b
{
    bool process(data d) override
    {
        if (d.flg == "add")
        {
            *d.ret = d.a + d.b;
            return true;
        }
        return false;
    }
};
struct test_b2 : public test_base_b
{
    bool process(data d) override
    {
        if (d.flg == "sub")
        {
            *d.ret = d.a - d.b;
            return true;
        }
        return false;
    }
};
struct test_b3 : public test_base_b
{
    bool process(data d) override
    {
        if (d.flg == "mul")
        {
            *d.ret = d.a * d.b;
            return true;
        }
        return false;
    }
};

void test_1()
{
    using namespace bhtools;
    {
        Twork_chain<test_a1, test_a2, test_a3> worka;
        bool ok1 = worka.start(1);
        bool ok2 = worka.start(12);
        bool ok3 = worka.start(123);
        bool ok4 = worka.start(1234);
        vlogd($(ok1) $(ok2) $(ok3) $(ok4));
    }
    {
        Twork_chain<test_b1, test_b2, test_b3> worka;
        test_base_b::data d;
        d.a = 10;
        d.b = 20;
        d.ret = std::make_shared<int>();
        d.flg = "add";
        bool ok = worka.start(d);
        vlogd($(ok) $(*d.ret));
    }
    {
        Twork_chain<test_b1, test_b2, test_b3> worka;
        test_base_b::data d;
        d.a = 10;
        d.b = 20;
        d.ret = std::make_shared<int>();
        d.flg = "sub";
        bool ok = worka.start(d);
        vlogd($(ok) $(*d.ret));
    }
    {
        Twork_chain<test_b1, test_b2, test_b3> worka;
        test_base_b::data d;
        d.a = 10;
        d.b = 20;
        d.ret = std::make_shared<int>();
        d.flg = "mul";
        bool ok = worka.start(d);
        vlogd($(ok) $(*d.ret));
    }
    {
        Twork_chain<test_b1, test_b2, test_b3> worka;
        test_base_b::data d;
        d.a = 10;
        d.b = 20;
        d.ret = std::make_shared<int>();
        d.flg = "exp";
        bool ok = worka.start(d);
        vlogd($(ok) $(*d.ret));
    }
}

int main(int argc, char *argv[])
{
    test_1();
    return 0;
}