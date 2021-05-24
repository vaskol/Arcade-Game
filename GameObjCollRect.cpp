#include "GameObjCollRect.h"


GameObjCollRect::GameObjCollRect(const Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size)
	: GameObject(mygame, gobj_pos_x, gobj_pos_y, gobj_size)
{
}

Rectangle GameObjCollRect::getCollisionHull(float width_factor, float height_factor) const
{
	return Rectangle(pos_x, pos_y, size*width_factor, size*height_factor);
}

