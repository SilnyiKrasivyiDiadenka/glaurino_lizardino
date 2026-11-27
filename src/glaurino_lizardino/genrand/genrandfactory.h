#ifndef GENRANDFACTORY_H
#define GENRANDFACTORY_H

#include "igenrand.h"
#include <memory>

namespace Glaurung {
enum class IMPL { STD };

class GenRandFactory
{
public:
    enum class IMPL { STD, G22_MERSENNE };

    static std::unique_ptr<IGenRand> Create(const IMPL impl = IMPL::STD);
};

} // namespace Glaurung

#endif // GENRANDFACTORY_H
