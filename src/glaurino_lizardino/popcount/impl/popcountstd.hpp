#ifndef POPCOUNTSTD_HPP
#define POPCOUNTSTD_HPP

#include "../ipopcount.h"
#include <bit>

namespace Glaurung {

class PopCountStd : public IPopCount
{
public:
    virtual ~PopCountStd() = default;

    constexpr std::size_t count_1s(const Bitboard &b) const override { return std::popcount(b); }

    constexpr std::size_t count_1s_max_15(const Bitboard &b) const override
    {
        return std::popcount(b);
    }

private:
    PopCountStd() = default;

    friend class PopCountFactory;
};

} // namespace Glaurung

#endif // POPCOUNTSTD_HPP
