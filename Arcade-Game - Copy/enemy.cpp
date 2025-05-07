#include "game.h"		//<--  (��� GameObject ???)
#include "Enemy.h"
#include "config.h"		//<--
#include "util.h"		//<--
#include <random>


Enemy::Enemy(const Game& mygame)
	: GameObjCollDisk(mygame, pos_x, pos_y, size)	//����� ��� constr ��� ��������. �� ����� ��������������� ���� init().
{

}

Enemy::~Enemy()		//��� ��� ���� �� ����������, ��� � destructor ��� ��� ����� ����.
{
}


void Enemy::update()
{
	GameObject::update();

	pos_x -= move()/50.0f;
}

/*
void Enemy::draw()		
{
	
}*/


/*
Shape* Enemy::getCollisionHull() const			//** CHECK inheritance return type --> ����. (++ const)		// explanation !!
{
	Disk* en_disk = new Disk(pos_x, pos_y, size * 0.45f);			// 0.42f ��� ��� ������ -> ����������.
	return en_disk;
}*/
