#pragma once

#include "GameObjCollDisk.h"		
#include "Movable.h"
#include "Bunker.h"


class Player : public GameObjCollDisk, public Movable
{
private:
	//float height = 1.0f;	//������������ ������� �� ��� �������� ��� �� ������������. (�����: ������� ���� ���� + �������� ��� ���� [��� ���������-����������, ��������� �� � ����]. )

	//graphics::Brush brush;	

public:
	Player(const class Game& mygame, float pl_pos_x, float pl_pos_y, float pl_size);

	void update() override;		//override: gia na kseroume oti pro-ilthe apo polymorphiki antikatastasi.
	void draw() override;
	void init() override;

	//Disk getCollisionHull() const override;
	//void checkStopByBunker(Bunker*& bun);
};
