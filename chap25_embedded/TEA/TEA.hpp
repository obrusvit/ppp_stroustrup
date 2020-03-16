#ifndef GUARD_TEA_ENCRYPTION_FROM_PPP
#define GUARD_TEA_ENCRYPTION_FROM_PPP

#include <cstdint>

namespace tea_ppp {

using Ulong = uint32_t;

void encipher(
        const Ulong * const v,
        Ulong * const w,
        const Ulong * const k
        ){
    static_assert(sizeof(Ulong)==4, "size of Ulong wrong for TEA");
    Ulong y = v[0];
    Ulong z = v[1];
    Ulong sum = 0;
    const Ulong delta = 0x9E3779B9;
    for (Ulong n  = 32; n-->0; ){
        y += (z<<4 ^ z>>5) + z^sum + k[sum&3];
        sum += delta;
        z += (y<<4 ^ y>>5) + y^sum + k[sum>>11 & 3];
    }
    w[0]=y;
    w[1]=z;
}

void decipher(
        const Ulong * const v,
        Ulong * const w,
        const Ulong * const k
        ){
    static_assert(sizeof(Ulong)==4, "size of Ulong wrong for TEA");
    Ulong y = v[0];
    Ulong z = v[1];
    Ulong sum = 0xC6EF3720;
    const Ulong delta = 0x9E3779B9;
    for (Ulong n = 32; n-->0; ){
        z -= (y<<4 ^ y>>5) + y^sum + k[sum>>11 & 3];
        sum -= delta;
        y -= (z<<4 ^ z>>5) + z^sum + k[sum&3];
    }
    w[0]=y;
    w[1]=z;
}

} //namespace tea_ppp

#endif

