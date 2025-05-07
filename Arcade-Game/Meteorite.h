#pragma once

#include "Enemy.h"


class Meteorite : public Enemy
{
protected:
	float rotation;			// ���� � ����������

	graphics::Brush brush;		//** CHECK (++tutorial) //

public:
	Meteorite(const class Game& mygame);		//�� ���� �����/���� ���� init().
	~Meteorite();

	void update() override;		//override: �� ����������� (��� �� ���������).
	void draw() override;
	void init() override;
	//Shape* getCollisionHull() const override;
};