#pragma once

#include "gameObject.h"


class GameObjCollRect : public GameObject		// class for game objects with rectangle collision hull.
{
protected:
	float width_factor=1.0f; 
	float height_factor=1.0f;

public:
	GameObjCollRect(const Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size);

	/*float get_width_factor() const { return width_factor; }
	void set_width_factor(float wf) { width_factor = wf; }

	float get_height_factor() const { return height_factor; }
	void set_height_factor(float hf) { height_factor = hf; }*/

	Rectangle getCollisionHull(float width_factor, float height_factor) const;
};
