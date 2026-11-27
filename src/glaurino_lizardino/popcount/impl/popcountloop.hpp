#ifndef POPCOUNTLOOP_HPP
#define POPCOUNTLOOP_HPP

#include "../ipopcount.h"

namespace Glaurung {

class PopCountLoop : public IPopCount
{
public:
    virtual ~PopCountLoop() = default;

    constexpr std::size_t count_1s(const Bitboard &b) const override
    {
        auto bTmp{b};
        int r;
        for (r = 0; bTmp; r++, bTmp &= bTmp - 1)
            ;
        return r;
    }

    constexpr std::size_t count_1s_max_15(const Bitboard &b) const override { return count_1s(b); }

private:
    PopCountLoop() = default;

    friend class PopCountFactory;
};

} // namespace Glaurung

#endif // POPCOUNTLOOP_HPP
