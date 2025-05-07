#pragma once

#include "Enemy.h"


class Meteorite : public Enemy
{
protected:
	float rotation;			// ΜΟΝΟ ο μετεωρίτης

	graphics::Brush brush;		//** CHECK (++tutorial) //

public:
	Meteorite(const class Game& mygame);		//Τα άλλα αρχικ/νται στην init().
	~Meteorite();

	void update() override;		//override: ως αναμνηστικό (για να θυμόμαστε).
	void draw() override;
	void init() override;
	//Shape* getCollisionHull() const override;
};