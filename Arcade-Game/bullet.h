#pragma once

#include <stdlib.h>		
#include "GameObjCollRect.h"
#include "Movable.h"

class Bullet : public GameObjCollRect, public Movable
{		
	graphics::Brush br;		
public:
	Bullet(const class Game& mygame, float bul_pos_x, float bul_pos_y /*, float bul_size*/);
	~Bullet();
	void update() override;
	void draw() override;
	void init() override;
};
