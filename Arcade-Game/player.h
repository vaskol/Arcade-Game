#pragma once

#include "GameObjCollDisk.h"		
#include "Movable.h"
#include "Bunker.h"


class Player : public GameObjCollDisk, public Movable
{
private:

public:
	Player(const class Game& mygame, float pl_pos_x, float pl_pos_y, float pl_size);

	void update() override;		
	void draw() override;
	void init() override;
};
