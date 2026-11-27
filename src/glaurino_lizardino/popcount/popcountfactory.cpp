#include "popcountfactory.h"

#include "impl/popcountloop.hpp"
#include "impl/popcountstd.hpp"
#include "impl/popcountswar32.hpp"
#include "impl/popcountswar64.hpp"

namespace Glaurung {

std::unique_ptr<Glaurung::IPopCount> Glaurung::PopCountFactory::Create(
    const PopCountFactory::IMPL impl)
{
    switch (impl) {
    case IMPL::STD:
        return std::unique_ptr<IPopCount>(new PopCountStd());
    case IMPL::G22_SWAR64:
        return std::unique_ptr<IPopCount>(new PopCountSwar64());
    case IMPL::G22_SWAR32:
        return std::unique_ptr<IPopCount>(new PopCountSwar32());
    case IMPL::G22_LOOP:
        return std::unique_ptr<IPopCount>(new PopCountLoop());
    }
    return nullptr;
}

} // namespace Glaurung
