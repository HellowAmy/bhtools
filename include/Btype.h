#ifndef BTYPE_H
#define BTYPE_H

#include <cstdint>
#include <string>

namespace bh {

// 有符号整数类型别名
using int08 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

// 无符号整数类型别名
using uint08 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

// 浮点数类型别名
using ft32 = float;
using ft64 = double;

// 标准字符串类型别名
using dstr = std::string;
using cstr = const std::string &;

// 字符指针类型别名
using dchp = char *;
using cchp = const char *;

// 常用位偏移常量定义
static constexpr uint32 _BH_INT_16_ = (1U << 4);
static constexpr uint32 _BH_INT_32_ = (1U << 5);
static constexpr uint32 _BH_INT_64_ = (1U << 6);
static constexpr uint32 _BH_INT_128_ = (1U << 7);
static constexpr uint32 _BH_INT_256_ = (1U << 8);
static constexpr uint32 _BH_INT_512_ = (1U << 9);
static constexpr uint32 _BH_INT_1024_ = (1U << 10);
static constexpr uint32 _BH_INT_2048_ = (1U << 11);
static constexpr uint32 _BH_INT_4096_ = (1U << 12);

// 最高位为1的值
static constexpr uint08 _BH_ONE_LOW_ = (1UL << 0);
static constexpr uint08 _BH_ONE_HIGH_INT08_ = (1UL << 7);
static constexpr uint16 _BH_ONE_HIGH_INT16_ = (1UL << 15);
static constexpr uint32 _BH_ONE_HIGH_INT32_ = (1UL << 31);
static constexpr uint64 _BH_ONE_HIGH_INT64_ = (1UL << 63);

// 16进制1248位为1的值bit位置
static constexpr uint08 _BH_ONE_HEX_1_ = (1UL << 0);
static constexpr uint08 _BH_ONE_HEX_2_ = (1UL << 1);
static constexpr uint08 _BH_ONE_HEX_4_ = (1UL << 2);
static constexpr uint08 _BH_ONE_HEX_8_ = (1UL << 3);

} // namespace bh

#endif // BTYPE_H