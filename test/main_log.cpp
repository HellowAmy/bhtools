
#include <iostream>

#include "Tlog.h"


using namespace std;
using namespace bhtools;

void print(string str)
{
    cout<<"<<<< "<<str<<endl;
}

int main(int argc, char *argv[])
{

    // using bhtools::bhlevel4::level;

    // level po;
    // po = level::e_debug;

    Tlog_buf buf;
    buf.value();

    Tlog_base<bhenum::level4,Tlog_buf,Tlog_end> base;
    const char *cp = "cc1122";
    std::string sp = "ss11";
    int isp = 5599;

    base<<bhenum::level4::e_debug;
    base<<123;
    base<<123.123;
    base<<"123";
    base<<cp;
    base<<sp;
    base<<Tlog_end();

    base<<bhenum::level4::e_debug;
    base<<123;
    base<<123.123;
    base<<"123";
    base<<cp;
    base<<sp;
    base<<isp;
    base<<Tlog_end();


    print("beign");

    print("end");
    return 0;
}