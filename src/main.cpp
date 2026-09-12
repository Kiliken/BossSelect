#include "bn_core.h"
#include "MapManager.h"
#include "bn_sprite_items_character.h" // Reusing the character sprite for the enemy
#include "bn_log.h"                    // Required for printing messages
#include "bn_keypad.h"                 // Added for the L button check
#include "bn_random.h"                 // Added for random number generation

#include "player.h"
#include "hud.h"
#include "Ship_Boss.h"

#include "bn_camera_ptr.h"

// --- Placeholder Enemy Class ---
class Enemy
{
private:
    bn::sprite_ptr _sprite;

public:
    Enemy(int start_x, int start_y) : _sprite(bn::sprite_items::character.create_sprite(start_x, start_y))
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

    // ***DEBUG for checking game over, remove or replace with proper game over logic later
    bool game_over = false;

    // Instantiate the player at X=0, Y=0
    Player player(0, 0);

    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

    MapManager map_manager(camera);

    player.sprite().set_camera(camera);

    // Instantiate the test boss slightly to the right (X=40, Y=0)
    ShipBoss shipBoss(bn::sprite_items::character.create_sprite(40, 0));

    HUD hud;

    while (true)
    {
        if (player.get_hp() > 0)
        {

            bn::fixed_point previous_position = player.position();

            // Run all player logic (movement, attacks, i-frames)
            player.update();
            shipBoss.Update();

            bn::fixed_point constrained_position =
                map_manager.constrain_player(
                    player.position(),
                    previous_position);

            player.set_position(
                constrained_position.x(),
                constrained_position.y());

            map_manager.update_camera(player.position());

            bn::fixed player_x = player.position().x();
            bn::fixed player_y = player.position().y();

            constexpr int EXIT_HALF_SIZE = 24;

            if (map_manager.current_map() == MapID::CENTER)
            {
                // TOP exit
                if (player_y <= -80 &&
                    player_x >= -EXIT_HALF_SIZE &&
                    player_x <= EXIT_HALF_SIZE)
                {
                    map_manager.change_map(MapID::TOP);
                    player.set_position(0, 100);
                }

                // BOTTOM exit
                else if (player_y >= 80 &&
                         player_x >= -EXIT_HALF_SIZE &&
                         player_x <= EXIT_HALF_SIZE)
                {
                    map_manager.change_map(MapID::BOTTOM);
                    player.set_position(0, -100);
                }

                // LEFT exit
                else if (player_x <= -120 &&
                         player_y >= -EXIT_HALF_SIZE &&
                         player_y <= EXIT_HALF_SIZE)
                {
                    map_manager.change_map(MapID::LEFT);
                    player.set_position(100, 0);
                }

                // RIGHT exit
                else if (player_x >= 120 &&
                         player_y >= -EXIT_HALF_SIZE &&
                         player_y <= EXIT_HALF_SIZE)
                {
                    map_manager.change_map(MapID::RIGHT);
                    player.set_position(-100, 0);
                }
            }

            if (map_manager.current_map() == MapID::TOP)
            {
                if (player_y >= 128 &&
                    player_x >= -EXIT_HALF_SIZE &&
                    player_x <= EXIT_HALF_SIZE)
                {
                    map_manager.change_map(MapID::CENTER);
                    player.set_position(0, -45);
                }
            }
            else if (map_manager.current_map() == MapID::BOTTOM)
            {
                if (player_y <= -128 &&
                    player_x >= -EXIT_HALF_SIZE &&
                    player_x <= EXIT_HALF_SIZE)
                {
                    map_manager.change_map(MapID::CENTER);
                    player.set_position(0, 45);
                }
            }
            else if (map_manager.current_map() == MapID::LEFT)
            {
                if (player_x >= 128 &&
                    player_y >= -EXIT_HALF_SIZE &&
                    player_y <= EXIT_HALF_SIZE)
                {
                    map_manager.change_map(MapID::CENTER);
                    player.set_position(-85, 0);
                }
            }
            else if (map_manager.current_map() == MapID::RIGHT)
            {
                if (player_x <= -128 &&
                    player_y >= -EXIT_HALF_SIZE &&
                    player_y <= EXIT_HALF_SIZE)
                {
                    map_manager.change_map(MapID::CENTER);
                    player.set_position(85, 0);
                }
            }

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

            {
            }

            if (utils::fixed::distance(player.position(), shipBoss.position()) < 12)
            {
                bn::fixed_rect player_box = player.get_collision_rect();
                bn::fixed_rect boss_box = shipBoss.hitbox();

                if (player_box.intersects(boss_box))
                {
                    player.take_damage(2);
                    bn::fixed_point direction = player.position() - shipBoss.position();
                    bn::fixed dist = utils::fixed::distance(player.position(), shipBoss.position());

                    if (dist > 0)
                    {
                        bn::fixed strength = 3;
                        bn::fixed force_x = (direction.x() / dist) * strength;
                        bn::fixed force_y = (direction.y() / dist) * strength;

                        player.apply_knockback(force_x, force_y);
                    }
                }
            }

            // --- Collision Check Logic ---
            if (player.is_attacking())
            {
                // Get both bounding boxes
                bn::fixed_rect sword_box = player.get_sword_hitbox();
                bn::fixed_rect boss_box = shipBoss.hitbox();

                // Check for AABB intersection
                if (sword_box.intersects(boss_box))
                {
                    shipBoss.TakeDamage(5);
                    BN_LOG("Boss life : %d", shipBoss.life());
                }
            }
            // -----------------------------
        }
        // GAME OVER CONDITION: If the player's HP is 0 or less, trigger game over
        else if (!game_over)
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