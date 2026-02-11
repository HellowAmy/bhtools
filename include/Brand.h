#ifndef BRAND_H
#define BRAND_H

#include <random>

namespace bh {

// 随机种子生成
template <typename Tdev = std::random_device, typename Tgen = std::mt19937_64>
struct Brand_gen
{
    Brand_gen() { _gen.seed(_rd()); }

    Tdev _rd;
    Tgen _gen;
};

// 整数与浮点分布计算
template <typename Tdis, typename T>
struct Brand_value : public Tdis, Brand_gen<>
{
    using Tdis::Tdis;
    T value() { return (*this)(_gen); }
};

//
//
//
//

// 快捷使用方式
using Brand_int = Brand_value<std::uniform_int_distribution<>, int32>;    // 均匀-整数分布
using Brand_double = Brand_value<std::uniform_real_distribution<>, ft64>; // 均匀-浮点分布
using Brand_bool = Brand_value<std::bernoulli_distribution, bool>;        // 均匀-布尔分布
using Brand_ndis = Brand_value<std::normal_distribution<>, ft64>;         // 正态-距离中间点扩散概率
using Brand_ddis = Brand_value<std::discrete_distribution<>, int32>;      // 离散-列表中下标出现概率
using Brand_pdis = Brand_value<std::poisson_distribution<>, int32>; // 泊松-模拟一小时内发生次数分布
using Brand_gdis = Brand_value<std::gamma_distribution<>, ft64>;    // 泊松-模拟所有事件发生总长分布

} // namespace bh

#endif // BRAND_H
