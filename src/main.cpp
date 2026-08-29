#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_testbg.h"

#include "player.h" 

int main()
{
    bn::core::init();

    bn::regular_bg_ptr bg = bn::regular_bg_items::testbg.create_bg(0, 0);

    // Instantiate the player at X=0, Y=0
    Player player(0, 0); 

    while(true)
    {
        // Run all player logic (movement, attacks, i-frames)
        player.update();

        // Render the frame
        bn::core::update(); 
    }
}