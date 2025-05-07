#pragma once

#include <stdlib.h>			//** CHECK
#include "GameObjCollRect.h"
#include "Movable.h"


class Bullet : public GameObjCollRect, public Movable
{
	//pos_x = 100, pos_y = CANVAS_HEIGHT/2;
	//size = 30;		// ��� draw()->drawRect
	//bool active = true;
	//float speed = 0.3f;			//���� init(): speed=0.4f

	graphics::Brush br;			//** CHECK -> ���� GameObject ??

public:
	Bullet(const class Game& mygame, float bul_pos_x, float bul_pos_y /*, float bul_size*/);
	~Bullet();

	void update() override;
	void draw() override;
	void init() override;
};
