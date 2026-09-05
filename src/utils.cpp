#include "utils.h"

bn::fixed utils::fixed::distance(const bn::fixed_point &p1, const bn::fixed_point &p2)
{
    bn::fixed dx = p2.x() - p1.x();
    bn::fixed dy = p2.y() - p1.y();
    return bn::sqrt((dx * dx) + (dy * dy));
}

bn::fixed_point utils::fixed::normalize(const bn::fixed_point &p)
{
    bn::fixed length = distance(bn::fixed_point(0, 0), p);
    if (length == 0)
    {
        return bn::fixed_point(0, 0); // Avoid division by zero
    }
    return bn::fixed_point(p.x() / length, p.y() / length);
}