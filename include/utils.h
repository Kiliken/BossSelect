#ifndef UTILS_H
#define UTILS_H

#include "bn_fixed_point.h"
#include "bn_math.h"

namespace utils
{
    namespace fixed{
        bn::fixed distance(const bn::fixed_point &p1, const bn::fixed_point &p2);
    }
}

#endif // UTILS_H