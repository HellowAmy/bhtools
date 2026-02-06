#include <iostream>

#include "Bfm.h"

#include "Ftest.h"



void test_1() {

    auto s1 = bh::Bfm("{}{}{}")(1,2,3);
    auto s2 = bh::Bfm("{}{}{}")(100,200,300);
    auto s3 = bh::Bfm("{}{}{}")(123,456,789);
    auto s4 = bh::Bfm("#{}#{}#{}#")(123,456,789);
    auto s5 = bh::Bfm("{}#{}#{}")(123,456,789);
    auto s6 = bh::Bfm("##{}##{}##{}##")(123,456,789);
    auto s7 = bh::Bfm("####{}####{}####{}####")(123,456,789);
    auto s8 = bh::Bfm("####{{}}####{{}}####{{}}####")(123,456,789);
    auto s9 = bh::Bfm("####{{#}}####{{#}}####{{#}}####")(123,456,789);

    vloga("边界检查");
    vlogd($(s1));
    vlogd($(s2));
    vlogd($(s3));
    vlogd($(s4));
    vlogd($(s5));
    vlogd($(s6));
    vlogd($(s7));
    vlogd($(s8));
    vlogd($(s9));
}

void test_2() {}

int main(int argc, char *argv[])
{
    test_1();
    // test_2();

    return 0;
}