#ifndef POPCOUNTFACTORY_H
#define POPCOUNTFACTORY_H

#include "ipopcount.h"
#include <memory>

namespace Glaurung {

class PopCountFactory
{
public:
    enum class IMPL { STD, G22_SWAR64, G22_SWAR32, G22_LOOP };

    static std::unique_ptr<IPopCount> Create(const IMPL impl = IMPL::STD);
};

} // namespace Glaurung

#endif //POPCOUNTFACTORY_H
