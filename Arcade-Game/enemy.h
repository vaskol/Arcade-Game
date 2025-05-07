#pragma once

#include "GameObjCollDisk.h"
#include "Movable.h"


class Enemy : public GameObjCollDisk, public Movable
{
protected:					

		

public:					
	Enemy(const class Game& mygame);
	virtual	~Enemy();		

	virtual void update() override;		

};
