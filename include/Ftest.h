
#ifndef FTEST_H
#define FTEST_H

#include "Tlog.h"

namespace bhtools {

// 测试宏
#define BHLOG_MAKE_COLYES(out,end,...) BHLOG_MAKE(out,"\033[32m[Yes]","\033[0m"<<end,e_deb,__VA_ARGS__)
#define BHLOG_MAKE_COLBAD(out,end,...) BHLOG_MAKE(out,"\033[31m[Bad]","\033[0m"<<end,e_deb,__VA_ARGS__)
#define BHLOG_YES(...) BHLOG_MAKE_COLYES(BHLOG_CONF_DEF(_cmd),BHLOG_CONF_DEF(_end),__VA_ARGS__)
#define BHLOG_BAD(...) BHLOG_MAKE_COLBAD(BHLOG_CONF_DEF(_cmd),BHLOG_CONF_DEF(_end),__VA_ARGS__)

// 值是否相等
#define BHTEST_EQUAL(a,b)                                                       \
    if(a == b)  { BHLOG_YES("[BHTEST_EQUAL] " << $(a) "== " << $(b)); }         \
    else        { BHLOG_BAD("[BHTEST_EQUAL] " << $(a) "!= " << $(b)); }         \


// 值是否为真
#define BHTEST_TRUE(ok)                                             \
    if(ok)  { BHLOG_YES("[BHTEST_TRUE] "<<$(ok)); }                 \
    else    { BHLOG_BAD("[BHTEST_TRUE] "<<$(ok)); }                 \


// 空提示
#define BHTEST_NULL(ptr)                                            \
    if(!ptr)  { BHLOG_BAD("[BHTEST_NULL] "<<$(ptr)); }              \

} // bhtools

#endif // FTEST_H
