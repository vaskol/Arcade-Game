#pragma once

#include <stdlib.h>			
#include "gameObject.h"



class Explosion : public GameObject		
{
protected:
	
	bool active = false;	
	float rotation;	
	float size;			
	float speed=0.0f;	
	
	graphics::Brush brush;	

public:
	void update() override;
	void draw() override;
	void init() override;

	Explosion(const Game& mygame, float bul_pos_x, float bul_pos_y);
	~Explosion();
};