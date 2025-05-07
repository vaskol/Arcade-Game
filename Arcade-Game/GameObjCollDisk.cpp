#include "GameObjCollDisk.h"


GameObjCollDisk::GameObjCollDisk(const Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size)
    : GameObject(mygame, gobj_pos_x, gobj_pos_y, gobj_size)
{
}

Disk GameObjCollDisk::getCollisionHull(float radius_factor) const
{
    return Disk(pos_x, pos_y, size*radius_factor);
}
