#ifndef POPCOUNTSWAR32_HPP
#define POPCOUNTSWAR32_HPP

#include "../ipopcount.h"

namespace Glaurung {

class PopCountSwar32 : public IPopCount
{
public:
    virtual ~PopCountSwar32() = default;

    constexpr std::size_t count_1s(const Bitboard &b) const override
    {
        unsigned w = unsigned(b >> 32), v = unsigned(b);
        v = v - ((v >> 1) & 0x55555555);
        w = w - ((w >> 1) & 0x55555555);
        v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
        w = (w & 0x33333333) + ((w >> 2) & 0x33333333);
        v = (v + (v >> 4)) & 0x0F0F0F0F;
        w = (w + (w >> 4)) & 0x0F0F0F0F;
        v = ((v + w) * 0x01010101) >> 24; // mul is fast on amd procs
        return int(v);
    }

    constexpr std::size_t count_1s_max_15(const Bitboard &b) const override
    {
        unsigned w = unsigned(b >> 32), v = unsigned(b);
        v = v - ((v >> 1) & 0x55555555);
        w = w - ((w >> 1) & 0x55555555);
        v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
        w = (w & 0x33333333) + ((w >> 2) & 0x33333333);
        v = ((v + w) * 0x11111111) >> 28;
        return int(v);
    }

private:
    PopCountSwar32() = default;

    friend class PopCountFactory;
};

} // namespace Glaurung

#endif // POPCOUNTSWAR32_HPP
