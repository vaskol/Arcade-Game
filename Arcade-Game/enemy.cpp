#include "game.h"		
#include "Enemy.h"
#include "config.h"		
#include "util.h"		
#include <random>

Enemy::Enemy(const Game& mygame)
	: GameObjCollDisk(mygame, pos_x, pos_y, size)	
{}
Enemy::~Enemy()		
{}

void Enemy::update()
{
	GameObject::update();
	pos_x -= move()/50.0f;
}
