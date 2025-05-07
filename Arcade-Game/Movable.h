#pragma once

#include "graphics.h"


class Movable			
{
protected:
	float speed = 0.0f;
	bool move_to_east = true;		// true: if the movable object moves from the left to the right side of canvas [player, playerBullet]. 
						// false: if the movable object moves from the right to the left side of canvas [meteorite, alien, alienBullet].
public:
	void set_move_to_east(bool d) { move_to_east = d; }
	float move() const;
	void setSpeed(float sp) { speed = sp; }
};
