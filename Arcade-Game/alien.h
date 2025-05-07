#pragma once

#include <iostream>
#include <string>
#include <vector>		
#include "Enemy.h"

class Alien : public Enemy
{
public:
	Alien(const class Game& mygame, float al_pos_x, float al_pos_y);
	~Alien();
	void update() override;
	void draw() override;
	void init() override;
};
