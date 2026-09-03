#include "bn_core.h"                        // Butano core functions
#include "bn_regular_bg_ptr.h"              // regular background pointers
#include "bn_regular_bg_items_testbg.h"     // the test background item

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_character.h" 
#include "bn_keypad.h"

#include "Ship_Boss.h"

int main()
{
    // Initialize the Butano core system
    bn::core::init();

    // Instantiate the background at the X, Y coordinates (0, 0)
    bn::regular_bg_ptr bg = bn::regular_bg_items::testbg.create_bg(0, 0);

    // Instantiate the sprite at X=0, Y=0
    bn::sprite_ptr character = bn::sprite_items::character.create_sprite(0, 0);

    ShipBoss testBoss(bn::sprite_items::character.create_sprite(0, 0));

    while(true)
    {
        // Poll the D-pad for movement
        if(bn::keypad::left_held())
        {
            character.set_x(character.x() - 1);
        }
        else if(bn::keypad::right_held())
        {
            character.set_x(character.x() + 1);
        }

        if(bn::keypad::up_held())
        {
            character.set_y(character.y() - 1);
        }
        else if(bn::keypad::down_held())
        {
            character.set_y(character.y() + 1);
        }

        testBoss.Update();

        bn::core::update(); // Render the frame
    }
}
