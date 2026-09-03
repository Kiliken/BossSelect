#include "utils.h"

bn::fixed utils::fixed::distance(const bn::fixed_point &p1, const bn::fixed_point &p2)
{
    bn::fixed dx = p2.x() - p1.x();
    bn::fixed dy = p2.y() - p1.y();
    return bn::sqrt((dx * dx) + (dy * dy));
}