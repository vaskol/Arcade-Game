#include "game.h"		//<--  (στο GameObject ???)
#include "Enemy.h"
#include "config.h"		//<--
#include "util.h"		//<--
#include <random>


Enemy::Enemy(const Game& mygame)
	: GameObjCollDisk(mygame, pos_x, pos_y, size)	//καλεί τον constr του προγόνου. Οι τιμές αρχικοποιούνται στην init().
{

}

Enemy::~Enemy()		//Δεν έχω κάτι να καταστρέψω, άρα ο destructor μου δεν κάνει κάτι.
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
Shape* Enemy::getCollisionHull() const			//** CHECK inheritance return type --> διάλ. (++ const)		// explanation !!
{
	Disk* en_disk = new Disk(pos_x, pos_y, size * 0.45f);			// 0.42f για τον μετεωρ -> παράμετρος.
	return en_disk;
}*/
