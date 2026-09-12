#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "bn_camera_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_fixed_point.h"

enum class MapID
{
    CENTER,
    TOP,
    LEFT,
    RIGHT,
    BOTTOM
};

class MapManager
{
public:
    explicit MapManager(bn::camera_ptr camera);
    

    void change_map(MapID map);
    void update_camera(const bn::fixed_point& player_position);

    bn::fixed_point constrain_player(
        const bn::fixed_point& position,
        const bn::fixed_point& previous_position
    ) const;

    bn::fixed map_left() const;
    bn::fixed map_top() const;
    bn::fixed map_right() const;
    bn::fixed map_bottom() const;

    MapID current_map() const
    {
        return _current_map;
    }

    
private:
    bn::camera_ptr _camera;
    bn::regular_bg_ptr _background;
    MapID _current_map = MapID::CENTER;
};

#endif