#pragma once

#include "GameObjCollDisk.h"
#include "Movable.h"


class Enemy : public GameObjCollDisk, public Movable
{
protected:					//κληρονομεί κι ο Alien (-> FIX)

	//graphics::Brush brush;		//-->για τον μετεωρίτη ήταν αυτό.		//** CHECK (++tutorial) //

public:						//public interface
	Enemy(const class Game& mygame);
	virtual	~Enemy();		//** CHECK

	virtual void update() override;		// <--
	//virtual void draw() = 0;		// <--
};
