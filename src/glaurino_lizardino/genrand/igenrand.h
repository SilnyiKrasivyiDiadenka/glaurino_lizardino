#ifndef IGENRAND_H
#define IGENRAND_H

#include <cstdint>

namespace Glaurung {

class IGenRand
{
public:
    virtual ~IGenRand() = default;

    virtual std::uint32_t genrand_uint32() = 0;
    virtual std::uint64_t genrand_uint64() = 0;
};

} // namespace Glaurung

#endif // IGENRAND_H
