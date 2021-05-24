#pragma once

#include "util.h"
#include "gameObject.h"


class GameObjCollDisk : public GameObject		// class for game objects with disk collision hull.
{
protected:
	//float radius_factor=0.5f;

public:
	GameObjCollDisk(const Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size);

	//virtual void update() = 0;

	//float get_radius_factor() const { return radius_factor; }
	//void set_radius_factor(float rf) { radius_factor = rf; }

	Disk getCollisionHull(float radius_factor) const;
};
