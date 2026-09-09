#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_testbg.h"
#include "bn_sprite_items_character.h"      // Reusing the character sprite for the enemy
#include "bn_log.h"                         // Required for printing messages
#include "bn_keypad.h"                      // Added for the L button check
#include "bn_random.h"                      // Added for random number generation

#include "player.h" 
#include "hud.h"


// --- Placeholder Enemy Class ---
class Enemy 
{
private:
    bn::sprite_ptr _sprite;
public:
    Enemy(int start_x, int start_y) : 
        _sprite(bn::sprite_items::character.create_sprite(start_x, start_y)) 
    {
    }

    bn::fixed_rect get_collision_rect() const 
    {
        return bn::fixed_rect(_sprite.x(), _sprite.y(), 16, 16);
    }
};
// -------------------------------


int main()
{
    bn::core::init();

    // Instantiate Butano's random generator
    bn::random random;

    bn::regular_bg_ptr bg = bn::regular_bg_items::testbg.create_bg(0, 0);

    // ***DEBUG for checking game over, remove or replace with proper game over logic later
    bool game_over = false;

    // Instantiate the player at X=0, Y=0
    Player player(0, 0); 

    // Instantiate the test enemy slightly to the right (X=40, Y=0)
    Enemy enemy(40, 0);

    HUD hud;

    while(true)
    {
        if(player.get_hp() > 0)
        {
            // Run all player logic (movement, attacks, i-frames)
            player.update();

            // Sync the HUD with the player's health
            hud.update(player.get_hp());

            // // --- Knockback Test Trigger ---
            // if(bn::keypad::l_pressed())
            // {
            //     // Generate a random int between 0 and 4, then subtract 2 to get a range of [-2, 2]
            //     bn::fixed random_dx = random.get_int(5) - 2;
            //     bn::fixed random_dy = random.get_int(5) - 2;
                
            //     // Ensure they don't roll (0, 0) and just stand still
            //     if(random_dx == 0 && random_dy == 0) { random_dx = 2; }

            //     player.apply_knockback(random_dx, random_dy);
            // }
            // // -----------------------------

            // damage test
            if(bn::keypad::l_pressed())
            {
                player.take_damage(4);
            }

            // --- Collision Check Logic ---
            if(player.is_attacking())
            {
                // Get both bounding boxes
                bn::fixed_rect sword_box = player.get_sword_hitbox();
                bn::fixed_rect enemy_box = enemy.get_collision_rect();

                // Check for AABB intersection
                if(sword_box.intersects(enemy_box))
                {
                    BN_LOG("Enemy hit");
                }
            }
            // -----------------------------
        }
        // GAME OVER CONDITION: If the player's HP is 0 or less, trigger game over
        else if(!game_over)
        {
            // Force the HUD to update one last time to show 0 hearts
            hud.update(0);

            BN_LOG("Player has been defeated!");
            game_over = true;
        }

        // Render the frame
        bn::core::update(); 
    }
}