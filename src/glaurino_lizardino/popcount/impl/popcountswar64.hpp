#ifndef POPCOUNTSWAR64_HPP
#define POPCOUNTSWAR64_HPP

#include "../ipopcount.h"

namespace Glaurung {

class PopCountSwar64 : public IPopCount
{
public:
    virtual ~PopCountSwar64() = default;

    constexpr std::size_t count_1s(const Bitboard &b) const override
    {
        auto result{b};
        result -= ((result >> 1) & 0x5555555555555555ULL);
        result = ((result >> 2) & 0x3333333333333333ULL) + (result & 0x3333333333333333ULL);
        result = ((result >> 4) + result) & 0x0F0F0F0F0F0F0F0FULL;
        result *= 0x0101010101010101ULL;
        return result >> 56;
    }

    constexpr std::size_t count_1s_max_15(const Bitboard &b) const override
    {
        auto result{b};
        result -= (result >> 1) & 0x5555555555555555ULL;
        result = ((result >> 2) & 0x3333333333333333ULL) + (result & 0x3333333333333333ULL);
        result *= 0x1111111111111111ULL;
        return result >> 60;
    }

private:
    PopCountSwar64() = default;

    friend class PopCountFactory;
};

} // namespace Glaurung

#endif // POPCOUNTSWAR64_HPP
