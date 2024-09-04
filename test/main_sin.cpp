

// #define BHLOG_CLOSE_LOG
// #define BHLOG_CLOSE_COL


#include <iostream>

#include "Tsin.h"
#include "Tlog.h"

using namespace bhtools;


class TastA : public Tsins<TastA>
{
    BHSIN_SIN(TastA,Tsins)
public:
    void print()
    {
        vlogd("hellow world A");
    }
};

class TastB
{
    BHSIN_SIN(TastB,Tsins)
public:
    void print()
    {
        vlogd("hellow world B");
    }
};

class TastC
{
public:
    void print()
    {
        vlogd("hellow world C");
    }
};

void test_1()
{
    TastA::get()->print();

    Tsins<TastB>::get()->print();

    Tsins<TastC>::get()->print();

    // TastA a;
    // a.print();

    // TastB b;
    // b.print();

    TastC c;
    c.print();

    Fexit a([](){
        vlogd("exit func");
    });
}

int main(int argc, char *argv[])
{


    test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    // test_5();
    // test_6();

    return 0;
}