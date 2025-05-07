#pragma once

#include <iostream>
#include <string>
#include <vector>		//<--

#include "Enemy.h"
//#include "config.h"		/*CHECK*/


class Alien : public Enemy
{

public:
	Alien(const class Game& mygame, float al_pos_x, float al_pos_y);
	~Alien( /*LOGIKA PREPEI NA KATASTREPSOUME KAPOU OLA TA ANTIKEIMENA,AFTO PREPEI NA TO DOUME SE MIA EPOMENH FASH */);
	void update() override;
	void draw() override;
	void init() override;
};
