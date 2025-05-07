#pragma once

#include "Enemy.h"


class Meteorite : public Enemy
{
protected:
	float rotation;			

	graphics::Brush brush;		

public:
	Meteorite(const class Game& mygame);		
	~Meteorite();

	void update() override;		
	void draw() override;
	void init() override;
};
