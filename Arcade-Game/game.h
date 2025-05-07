#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <string>

#include "config.h"
#include "gameobject.h"
#include "player.h"
#include "Meteorite.h"
#include "alien.h"
#include "bullet.h"
#include "explosion.h"
#include "Bunker.h"
#include "PNG.h"

using namespace std;

class Game
{
	bool debug_mode = false;
	int meteoKills = 0;
	int alienKills = 0;
	float gameOverTime = 0.0f;
	int score = 0;//deltatime ?
	int remainingTime = 0;

	Player* player = nullptr;			
	bool player_initialized = false;
	Bullet* playerBullet = nullptr;
	bool plBullet_initialized = false;
	Bullet* alienBullet = nullptr;
	bool alBullet_initialized = false;
	Meteorite* meteorite = nullptr;
	bool meteorite_initialized = false;
	Explosion* explosion = nullptr;		
	bool explosion_initialized = false;	

	std::vector<Bunker*> bunkers;		
	bool bunkers_initialized = false;

	std::list<Alien*> alienCol1;
	std::list<Alien*> alienCol2;
	std::list<Alien*> alienCol3;
	std::list<Alien*>::iterator list_it;
	
	std::vector< list<Alien*> > aliens;
	std::vector< list<Alien*> >::iterator vec_it;
	bool aliens_initialized = false;

	PNG playerPNG = PNG(2128.0f / 2117.0f, -90.0f, "spaceship.png", "spaceship-shadow.png");
	PNG bunkerPNG = PNG(66.0f / 140.0f, 0.0f, "bunkers\\bunker_1x2_top.png", "bunkers\\bunker_1x2_top-shadow.png");
	PNG alienPNG = PNG(421.0f / 564.0f, -90.0f /*CHECK*/, "aliens\\alien.png", "aliens\\alien-shadow.png");
	PNG meteoritePNG = PNG(512.0f / 512.0f, 0.0f, "meteorite.png", "meteorite-shadow.png");
	PNG playerBulletPNG = PNG(500.0f / 500.0f, 90.0f, "bullets\\green-bullet.png", "bullets\\green-bullet-shadow.png");
	PNG alienBulletPNG = PNG(1047.0f / 400.0f, 90.0f, "bullets\\red-bullet.png", "bullets\\red-bullet-shadow.png");
	PNG explosionPNG = PNG(512.0f / 512.0f, 0.0f, "explosions\\explosion.png", "" /*CHECK*/);

	Disk playerHull;
	Disk alienHull;
	Disk meteoriteHull;
	Rectangle bunkerHull;
	Rectangle playerBulletHull;		
	Rectangle alienBulletHull;		

	unsigned int window_width = WINDOW_WIDTH,
				 window_height = WINDOW_HEIGHT;

	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_PAUSE, STATUS_GAME_OVER } status_t;		
	status_t status = STATUS_START;							
	void checkMeteorite();
	void checkBullet(Bullet*& sh_bull);
	void checkAlien();	
	void spawnMeteorite();
	void shootBullet(Bullet*& sh_bullet, float sh_pos_x, float sh_pos_y, bool sh);	
	bool checkCollision_Cir_Cir(Disk& disk_1, Disk& disk_2);				
	bool checkCollision_Rec_Cir(Rectangle& rect, Disk& disk);				
	bool checkCollision_Rec_Rec(Rectangle& rec1, Rectangle& rec2);		

	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	void updatePauseScreen();

	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
	void drawPauseScreen();

public:
	void update();	
	void draw();
	void init();	
	void musicInit();

	unsigned int getWindowWidth() { return window_width; }		
	unsigned int getWindowHeight() { return window_height; }

	float window2canvasX(float x);		
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	void setDebugMode(bool d) { debug_mode = d; }	
	bool getDebugMode() const { return debug_mode; }	

	void setPauseTime(float t) { remainingTime = t; }		
	float getPauseTime() const { return remainingTime; }	

	void setStartime(float t) { remainingTime = t; }		
	float getStartTime() const { return remainingTime; }	

	void setTime(float t) { remainingTime = t; }
	float getTime() const { return remainingTime; }

	Game();
	~Game();
};
