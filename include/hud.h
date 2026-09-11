#ifndef HUD_H
#define HUD_H

#include "bn_sprite_ptr.h"
#include "bn_vector.h"

class HUD 
{
private:
    // A fixed-size vector to hold exactly 12 sprite pointers
    bn::vector<bn::sprite_ptr, 12> _heart_sprites;

public:
    HUD();

    // Call this every frame to sync the hearts with the player's current HP
    void update(int current_hp);
};

#endif // HUD_H