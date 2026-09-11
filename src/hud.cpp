#include "hud.h"
#include "bn_sprite_items_ui_hp.h"
#include "bn_sprite_tiles_ptr.h"


HUD::HUD() 
{
    // Define the starting coordinates (Top-Left of the screen with padding)
    int start_x = -112; 
    int start_y = -72;
    int spacing = 10; // 8 pixels for the sprite + 2 pixels of gap space

    for(int i = 0; i < 12; i++)
    {
        // Calculate grid position (2 rows of 6)
        int col = i % 6;
        int row = i / 6;

        int x = start_x + (col * spacing);
        int y = start_y + (row * spacing);

        // Instantiate all 12 sprites. We default them to frame 0 (full heart).
        // The .push_back() method adds them to our Butano vector.
        _heart_sprites.push_back(bn::sprite_items::ui_hp.create_sprite(x, y, 0));
    }
}


void HUD::update(int current_hp) 
{
    // Ensure HP stays within bounds to prevent array errors
    if(current_hp < 0) current_hp = 0;
    if(current_hp > 12) current_hp = 12;

    for(int i = 0; i < 12; i++)
    {
        if(i < current_hp)
        {
            // Set to Full Heart (Frame 0)
            _heart_sprites[i].set_tiles(bn::sprite_items::ui_hp.tiles_item().create_tiles(0));
        }
        else
        {
            // Set to Empty Heart (Frame 1)
            _heart_sprites[i].set_tiles(bn::sprite_items::ui_hp.tiles_item().create_tiles(1));
        }
    }
}