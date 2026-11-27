#ifndef GENRANDMERSENNE_HPP
#define GENRANDMERSENNE_HPP

#include "../igenrand.h"
#include <array>
#include <cstdlib>
#include <vector>

namespace Glaurung {

class GenRandMersenne : public IGenRand
{
public:
    virtual ~GenRandMersenne() = default;

    /* generates a random number on [0,0xffffffff]-interval */
    std::uint32_t genrand_uint32() override
    {
        std::uint32_t y;
        const std::array<std::uint32_t, 2> mag01 = {0x0UL, MATRIX_A};
        /* mag01[x] = x * MATRIX_A  for x=0,1 */

        if (mti >= N) { /* generate N words at one time */
            int kk;

            if (mti == N + 1)         /* if init_genrand() has not been called, */
                init_genrand(5489UL); /* a default initial seed is used */

            for (kk = 0; kk < N - M; kk++) {
                y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
                mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
            }
            for (; kk < N - 1; kk++) {
                y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
                mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
            }
            y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
            mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

            mti = 0;
        }

        y = mt[mti++];

        /* Tempering */
        y ^= (y >> 11);
        y ^= (y << 7) & 0x9d2c5680UL;
        y ^= (y << 15) & 0xefc60000UL;
        y ^= (y >> 18);

        return y;
    }

    std::uint64_t genrand_uint64() override
    {
        const std::uint64_t x{genrand_uint32()};
        const std::uint64_t y{genrand_uint32()};
        return (x << 32) | y;
    }

private:
    /* Period parameters */
    static const std::uint32_t N = 624;
    static const std::uint32_t M = 397;
    static const std::uint32_t MATRIX_A = 0x9908b0dfUL;   /* constant vector a */
    static const std::uint32_t UPPER_MASK = 0x80000000UL; /* most significant w-r bits */
    static const std::uint32_t LOWER_MASK = 0x7fffffffUL; /* least significant r bits */

    std::array<std::uint32_t, N> mt; /* the array for the state vector */
    std::size_t mti = N + 1;         /* mti==N+1 means mt[N] is not initialized */

    GenRandMersenne() { init_mersenne(); }

    void init_mersenne(void)
    {
        std::vector<std::uint32_t> init = {0x123, 0x234, 0x345, 0x456};
        init_by_array(init);
    }

    /* initializes mt[N] with a seed */
    void init_genrand(std::uint32_t s)
    {
        mt[0] = s & 0xffffffffUL;
        for (mti = 1; mti < N; mti++) {
            mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
            /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
            /* In the previous versions, MSBs of the seed affect   */
            /* only MSBs of the array mt[].                        */
            /* 2002/01/09 modified by Makoto Matsumoto             */
            mt[mti] &= 0xffffffffUL;
            /* for >32 bit machines */
        }
    }

    /* initialize by an array with array-length */
    /* init_key is the array for initializing keys */
    /* key_length is its length */
    /* slight change for C++, 2004/2/26 */
    void init_by_array(std::vector<std::uint32_t> &init_key)
    {
        int i, j, k;
        init_genrand(19650218UL);
        i = 1;
        j = 0;
        k = (N > init_key.size() ? N : init_key.size());
        for (; k; k--) {
            mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1664525UL)) + init_key[j]
                    + j;           /* non linear */
            mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
            i++;
            j++;
            if (i >= N) {
                mt[0] = mt[N - 1];
                i = 1;
            }
            if (j >= init_key.size())
                j = 0;
        }
        for (k = N - 1; k; k--) {
            mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1566083941UL)) - i; /* non linear */
            mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
            i++;
            if (i >= N) {
                mt[0] = mt[N - 1];
                i = 1;
            }
        }

        mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
    }

    friend class GenRandFactory;
};

} // namespace Glaurung

#endif // GENRANDMERSENNE_HPP
