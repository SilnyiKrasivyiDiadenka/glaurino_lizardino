#include "genrandfactory.h"
#include "impl/genrandmersenne.hpp"
#include "impl/genrandstd.hpp"

namespace Glaurung {

std::unique_ptr<Glaurung::IGenRand> Glaurung::GenRandFactory::Create(const GenRandFactory::IMPL impl)
{
    switch (impl) {
    case IMPL::STD:
        return std::unique_ptr<IGenRand>(new GenRandStd());
    case IMPL::G22_MERSENNE:
        return std::unique_ptr<IGenRand>(new GenRandMersenne());
    }
    return nullptr;
}

} // namespace Glaurung
