#ifndef BTYPE_H
#define BTYPE_H

#include <cstdint>
#include <string>

namespace bh {

//
using int08 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

//
using uint08 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

//
using ft32 = float;
using ft64 = double;

//
using dstr = std::string;
using rstr = std::string &;
using cstr = const std::string &;

//
using dchr = char;
using dchp = char *;
using cchp = const char *;

} // namespace bh

#endif // BTYPE_H
