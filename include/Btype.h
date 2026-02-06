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
uint32 _BH_INT_16_ = (1U << 4);
uint32 _BH_INT_32_ = (1U << 5);
uint32 _BH_INT_64_ = (1U << 6);
uint32 _BH_INT_128_ = (1U << 7);
uint32 _BH_INT_256_ = (1U << 8);
uint32 _BH_INT_512_ = (1U << 9);
uint32 _BH_INT_1024_ = (1U << 10);
uint32 _BH_INT_2048_ = (1U << 11);
uint32 _BH_INT_4096_ = (1U << 12);

} // namespace bh

#endif // BTYPE_H