#ifndef GENRANDSTD_HPP
#define GENRANDSTD_HPP

#include "../igenrand.h"
#include <random>

namespace Glaurung {

class GenRandStd : public IGenRand
{
public:
    virtual ~GenRandStd() = default;

    std::uint32_t genrand_uint32() override { return distU32_(rng_); }

    std::uint64_t genrand_uint64() override { return distU64_(rng_); }

private:
    std::mt19937 rng_{std::random_device{}()};

    std::uniform_int_distribution<std::uint32_t> distU32_{std::numeric_limits<std::uint32_t>::min(),
                                                          std::numeric_limits<std::uint32_t>::max()};

    std::uniform_int_distribution<std::uint64_t> distU64_{std::numeric_limits<std::uint64_t>::min(),
                                                          std::numeric_limits<std::uint64_t>::max()};

    GenRandStd() = default;

    friend class GenRandFactory;
};

} // namespace Glaurung

#endif // GENRANDSTD_HPP
