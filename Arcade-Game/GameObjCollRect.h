#pragma once

#include "gameObject.h"

class GameObjCollRect : public GameObject	
{
protected:
	float width_factor=1.0f; 
	float height_factor=1.0f;

public:
	GameObjCollRect(const Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size);
	Rectangle getCollisionHull(float width_factor, float height_factor) const;
};
