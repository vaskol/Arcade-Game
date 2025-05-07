#pragma once

#include "GameObjCollRect.h"



class Bunker : public GameObjCollRect
{
protected:			//<--
	float height_size = 100.0f;		//the height (3rd) dimension of the Bunker (ground to top).

	//graphics::Brush br;		/*test*/

public:
	Bunker(const class Game& myGame, float bun_pos_x, float bun_pos_y, float bun_top_side_size);
	~Bunker();
	
	void update() override;
	void draw() override;
	void init() override;
};