#include "MapManager.h"

#include "bn_regular_bg_items_mainmap.h"
#include "bn_regular_bg_items_bossmaptop.h"
#include "bn_regular_bg_items_bossmapbot.h"
#include "bn_regular_bg_items_bossmapleft.h"
#include "bn_regular_bg_items_bossmapright.h"

MapManager::MapManager(bn::camera_ptr camera) :
    _camera(camera),
    _background(bn::regular_bg_items::mainmap.create_bg(0, 0))
{
    _background.set_camera(_camera);
}

void MapManager::change_map(MapID map)
{
    _current_map = map;

    switch(map)
    {
        case MapID::CENTER:
            _background = bn::regular_bg_items::mainmap.create_bg(0, 0);
            _camera.set_position(0, 0);
            break;

        case MapID::TOP:
            _background = bn::regular_bg_items::bossmaptop.create_bg(0, 0);
            _camera.set_position(0, 48);
            break;

        case MapID::BOTTOM:
            _background = bn::regular_bg_items::bossmapbot.create_bg(0, 0);
            _camera.set_position(0, -48);
            break;

        case MapID::LEFT:
            _background = bn::regular_bg_items::bossmapleft.create_bg(0, 0);
            _camera.set_position(8, 0);
            break;

        case MapID::RIGHT:
            _background = bn::regular_bg_items::bossmapright.create_bg(0, 0);
            _camera.set_position(-8, 0);
            break;
    }

    _background.set_camera(_camera);
}


void MapManager::update_camera(const bn::fixed_point& player_position)
{
    // The center map is approximately one screen, so don't scroll it.
    if(_current_map == MapID::CENTER)
    {
        _camera.set_position(0, 0);
        return;
    }

    constexpr int CAMERA_DEADZONE_X = 70;
    constexpr int CAMERA_DEADZONE_Y = 45;

    bn::fixed player_screen_x = player_position.x() - _camera.x();
    bn::fixed player_screen_y = player_position.y() - _camera.y();

    // Horizontal camera movement
    if(player_screen_x > CAMERA_DEADZONE_X)
    {
        _camera.set_x(player_position.x() - CAMERA_DEADZONE_X);
    }
    else if(player_screen_x < -CAMERA_DEADZONE_X)
    {
        _camera.set_x(player_position.x() + CAMERA_DEADZONE_X);
    }

    // Vertical camera movement
    if(player_screen_y > CAMERA_DEADZONE_Y)
    {
        _camera.set_y(player_position.y() - CAMERA_DEADZONE_Y);
    }
    else if(player_screen_y < -CAMERA_DEADZONE_Y)
    {
        _camera.set_y(player_position.y() + CAMERA_DEADZONE_Y);
    }


    // 256x256 map:
    // screen = 240x160
    // max camera movement = (256-240)/2 = 8 horizontally
    //                       (256-160)/2 = 48 vertically

    constexpr int CAMERA_MAX_X = 8;
    constexpr int CAMERA_MAX_Y = 48;

    if(_camera.x() > CAMERA_MAX_X)
    {
        _camera.set_x(CAMERA_MAX_X);
    }
    else if(_camera.x() < -CAMERA_MAX_X)
    {
        _camera.set_x(-CAMERA_MAX_X);
    }

    if(_camera.y() > CAMERA_MAX_Y)
    {
        _camera.set_y(CAMERA_MAX_Y);
    }
    else if(_camera.y() < -CAMERA_MAX_Y)
    {
        _camera.set_y(-CAMERA_MAX_Y);
    }
}

bn::fixed_point MapManager::constrain_player(
    const bn::fixed_point& position,
    const bn::fixed_point& previous_position
) const
{
    bn::fixed x = position.x();
    bn::fixed y = position.y();

    bn::fixed previous_x = previous_position.x();
    bn::fixed previous_y = previous_position.y();

    constexpr int DOOR_HALF_SIZE = 8;
    constexpr int WALL_THICKNESS = 30;


    // CENTER MAP
    if(_current_map == MapID::CENTER)
    {
        constexpr int WALL_X = 120 - WALL_THICKNESS;
        constexpr int WALL_Y = 80 - WALL_THICKNESS;


        // LEFT vertical wall rectangles
        if(x < -WALL_X &&
           (y < -DOOR_HALF_SIZE || y > DOOR_HALF_SIZE))
        {
            // Came from inside the room
            if(previous_x >= -WALL_X)
            {
                x = -WALL_X;
            }
            // Already inside the hallway
            else
            {
                if(y < -DOOR_HALF_SIZE)
                {
                    y = -DOOR_HALF_SIZE;
                }
                else
                {
                    y = DOOR_HALF_SIZE;
                }
            }
        }


        // RIGHT vertical wall rectangles
        if(x > WALL_X &&
           (y < -DOOR_HALF_SIZE || y > DOOR_HALF_SIZE))
        {
            if(previous_x <= WALL_X)
            {
                x = WALL_X;
            }
            else
            {
                if(y < -DOOR_HALF_SIZE)
                {
                    y = -DOOR_HALF_SIZE;
                }
                else
                {
                    y = DOOR_HALF_SIZE;
                }
            }
        }


        // TOP horizontal wall rectangles
        if(y < -WALL_Y &&
           (x < -DOOR_HALF_SIZE || x > DOOR_HALF_SIZE))
        {
            if(previous_y >= -WALL_Y)
            {
                y = -WALL_Y;
            }
            else
            {
                if(x < -DOOR_HALF_SIZE)
                {
                    x = -DOOR_HALF_SIZE;
                }
                else
                {
                    x = DOOR_HALF_SIZE;
                }
            }
        }


        // BOTTOM horizontal wall rectangles
        if(y > WALL_Y &&
           (x < -DOOR_HALF_SIZE || x > DOOR_HALF_SIZE))
        {
            if(previous_y <= WALL_Y)
            {
                y = WALL_Y;
            }
            else
            {
                if(x < -DOOR_HALF_SIZE)
                {
                    x = -DOOR_HALF_SIZE;
                }
                else
                {
                    x = DOOR_HALF_SIZE;
                }
            }
        }
    }


    // TOP BOSS MAP
    // Hallway is at the BOTTOM.
    else if(_current_map == MapID::TOP)
    {
        constexpr int WALL = 128 - WALL_THICKNESS;

        // Left wall
        if(x < -WALL)
        {
            x = -WALL;
        }

        // Right wall
        if(x > WALL)
        {
            x = WALL;
        }

        // Top wall
        if(y < -WALL)
        {
            y = -WALL;
        }

        // Bottom wall + hallway
        if(y > WALL &&
           (x < -DOOR_HALF_SIZE || x > DOOR_HALF_SIZE))
        {
            // Hit wall from inside room
            if(previous_y <= WALL)
            {
                y = WALL;
            }
            // Already inside hallway and hit its side
            else
            {
                if(x < -DOOR_HALF_SIZE)
                {
                    x = -DOOR_HALF_SIZE;
                }
                else
                {
                    x = DOOR_HALF_SIZE;
                }
            }
        }
    }


    // BOTTOM BOSS MAP
    // Hallway is at the TOP.
    else if(_current_map == MapID::BOTTOM)
    {
        constexpr int WALL = 128 - WALL_THICKNESS;

        // Left wall
        if(x < -WALL)
        {
            x = -WALL;
        }

        // Right wall
        if(x > WALL)
        {
            x = WALL;
        }

        // Bottom wall
        if(y > WALL)
        {
            y = WALL;
        }

        // Top wall + hallway
        if(y < -WALL &&
           (x < -DOOR_HALF_SIZE || x > DOOR_HALF_SIZE))
        {
            if(previous_y >= -WALL)
            {
                y = -WALL;
            }
            else
            {
                if(x < -DOOR_HALF_SIZE)
                {
                    x = -DOOR_HALF_SIZE;
                }
                else
                {
                    x = DOOR_HALF_SIZE;
                }
            }
        }
    }


    // LEFT BOSS MAP
    // Hallway is at the RIGHT.
    else if(_current_map == MapID::LEFT)
    {
        constexpr int WALL = 128 - WALL_THICKNESS;

        // Top wall
        if(y < -WALL)
        {
            y = -WALL;
        }

        // Bottom wall
        if(y > WALL)
        {
            y = WALL;
        }

        // Left wall
        if(x < -WALL)
        {
            x = -WALL;
        }

        // Right wall + hallway
        if(x > WALL &&
           (y < -DOOR_HALF_SIZE || y > DOOR_HALF_SIZE))
        {
            if(previous_x <= WALL)
            {
                x = WALL;
            }
            else
            {
                if(y < -DOOR_HALF_SIZE)
                {
                    y = -DOOR_HALF_SIZE;
                }
                else
                {
                    y = DOOR_HALF_SIZE;
                }
            }
        }
    }


    // RIGHT BOSS MAP
    // Hallway is at the LEFT.
    else if(_current_map == MapID::RIGHT)
    {
        constexpr int WALL = 128 - WALL_THICKNESS;

        // Top wall
        if(y < -WALL)
        {
            y = -WALL;
        }

        // Bottom wall
        if(y > WALL)
        {
            y = WALL;
        }

        // Right wall
        if(x > WALL)
        {
            x = WALL;
        }

        // Left wall + hallway
        if(x < -WALL &&
           (y < -DOOR_HALF_SIZE || y > DOOR_HALF_SIZE))
        {
            if(previous_x >= -WALL)
            {
                x = -WALL;
            }
            else
            {
                if(y < -DOOR_HALF_SIZE)
                {
                    y = -DOOR_HALF_SIZE;
                }
                else
                {
                    y = DOOR_HALF_SIZE;
                }
            }
        }
    }


    return bn::fixed_point(x, y);
}