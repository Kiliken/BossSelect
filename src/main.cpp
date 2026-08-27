#include "bn_core.h"                        // Butano core functions
#include "bn_regular_bg_ptr.h"              // regular background pointers
#include "bn_regular_bg_items_testbg.h"     // the test background item

int main()
{
    // Initialize the Butano core system
    bn::core::init();

    // Instantiate the background at the X, Y coordinates (0, 0)
    bn::regular_bg_ptr bg = bn::regular_bg_items::testbg.create_bg(0, 0);

    while(true)
    {
        bn::core::update();
    }
}
