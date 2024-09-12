
#ifndef FTEST_H
#define FTEST_H

#include "Tlog.h"

namespace bhtools {


// 
#define BHTEST_EQUAL(a,b)                                       \
    if(a == b)  vlogd("[SUCC] [BHTEST_EQUAL] "<<$(a)$(b));      \
    else        vloge("[FAIL] [BHTEST_EQUAL] "<<$(a)$(b));      \


// 
#define BHTEST_TRUE(ok)                                         \
    if(ok)  vlogd("[SUCC] [BHTEST_TRUE] "<<$(ok));              \
    else    vloge("[FAIL] [BHTEST_TRUE] "<<$(ok));              \

    


} // bhtools





#endif // FTEST_H
