#ifndef IPOPCOUNT_H
#define IPOPCOUNT_H

#include "../../bitboard.h"

namespace Glaurung {

class IPopCount
{
public:
    virtual ~IPopCount() = default;

    /// count_1s() counts the number of nonzero bits in a bitboard.
    virtual constexpr std::size_t count_1s(const Bitboard &b) const = 0;
    virtual constexpr std::size_t count_1s_max_15(const Bitboard &b) const = 0;
};

} // namespace Glaurung

#endif // IPOPCOUNT_H
