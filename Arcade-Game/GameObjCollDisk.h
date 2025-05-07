#pragma once

#include "util.h"
#include "gameObject.h"


class GameObjCollDisk : public GameObject		
{
protected:

public:
	GameObjCollDisk(const Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size);
	Disk getCollisionHull(float radius_factor) const;
};
