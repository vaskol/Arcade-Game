#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <string>

//#include "util.h"
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

	/*score*/
	int meteoKills = 0;
	int alienKills = 0;
	float gameOverTime = 0.0f;
	int score = 0;//deltatime ?
	int remainingTime = 0;

	Player* player = nullptr;			//Mporei enas player na yparxei i na min yparxei. Ara to bazoume pointer (gia na mporei na arxikopoiithei me null). Theloume o paixtis na min emfanizetai amesos, alla meta apo ligo xrono.
	bool player_initialized = false;
	Bullet* playerBullet = nullptr;
	bool plBullet_initialized = false;
	Bullet* alienBullet = nullptr;
	bool alBullet_initialized = false;
	Meteorite* meteorite = nullptr;
	bool meteorite_initialized = false;
	Explosion* explosion = nullptr;		//** CHECK
	bool explosion_initialized = false;		// <--

	std::vector<Bunker*> bunkers;		//GameObject* αντί για Bunker* -> για τις checkCollisions.
	bool bunkers_initialized = false;

	// One list for each column of the aliens' group.
	//std::list<Alien*> alienListCol;

	std::list<Alien*> alienCol1;
	std::list<Alien*> alienCol2;
	std::list<Alien*> alienCol3;

	std::list<Alien*>::iterator list_it;
	
	// Each position of the vector contains one list that represents the corresponded column of the aliens' group.
	std::vector< list<Alien*> > aliens;
	std::vector< list<Alien*> >::iterator vec_it;
	bool aliens_initialized = false;

	//Enemy* meteorite = nullptr;		//TO-DO: ΛΙΣΤΑ με πολλούς μετεωρίτες.
										//Pointer, για να δημιουργηθεί επιτόπου, κάποια στιγμή. ΣΥΜΒΑΣΗ: στο παιχν ανά πάσα στιγμή, μόνο 1 μετεωρίτης θα είναι. 
										//Θα ήθελα, όταν είναι NULL ο μετεωρίτης, να δημιουργείται όταν δεν είναι NULL και συνεχίζει να υπάρχει (πριν καταστραφεί, πριν συμβεί οτιδήποτε που τον ακυρώνει), να μην μπορώ να παράγω άλλον.

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
	Rectangle playerBulletHull;		// player bullet collision hull.
	Rectangle alienBulletHull;		// alien bullet collision hull.

	unsigned int window_width = WINDOW_WIDTH,
				 window_height = WINDOW_HEIGHT;

	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_PAUSE, STATUS_GAME_OVER } status_t;		//τύπος που παίρνει 4 ακέραιες καταστάσεις (και ΜΟΝΟ αυτές).
	status_t status = STATUS_START;		//μεταβλητή κατάστασης για τις διαφορετικές οθόνες.	Τιμές: με enum (όπως εδώ) ή define. Το status να είναι τύπου status_t να παίρνει 1 από τις 2 τιμές ως αρχική.
										//θα πρέπει να την ελέγχουμε αυτήν την κατάσταση. (ελέγχουμε πράγματα στην update: βλέπουμε και κάνουμε update καταστάσεις.)
	//void checkActive(GameObject*& game_obj);		// η έκρηξη ξέρουμε πότε τελειώνει.
	void checkMeteorite();
	void checkBullet(Bullet*& sh_bull);
	//void checkBunker();
	void checkAlien();		// <--

	void spawnMeteorite();
	void shootBullet(Bullet*& sh_bullet, float sh_pos_x, float sh_pos_y, bool sh);	// pass pointer by reference
	//void createExplosion();

	bool checkCollision_Cir_Cir(Disk& disk_1, Disk& disk_2);				// intersection test circle-circle.
	bool checkCollision_Rec_Cir(Rectangle& rect, Disk& disk);				// intersection test rectangle-circle.
	bool checkCollision_Rec_Rec(Rectangle& rec1, Rectangle& rec2);		// intersection test rectangle-rectangle.

	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	void updatePauseScreen();

	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
	void drawPauseScreen();

public:
	void update();	//Εδώ θα καλέσω την spawnMeteorite(). Η update() είναι υπεύθυνη για το Game logic.
	void draw();
	void init();	//Called to begin the data inside the class and to do some things post-construction. Maybe doesn't need. init(): kaleitai prin mpo sto messageloop.
	void musicInit(/*status_t status*/);

	unsigned int getWindowWidth() { return window_width; }		//get -> expose τις 2 τιμές, για να μπορώ να αντικαταστήσω τις αρχικές μ' αυτές εδώ, όπου χρειαστεί.
	unsigned int getWindowHeight() { return window_height; }

	float window2canvasX(float x);		//μετατροπή μονάδων: αν μου δώσεις μια μονάδα σε window να την κάνω σε canvas.
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	//set -> γιατί θα πρέπει να ενημερώνω το αντικείμενο (το game), όταν οι διαστάσεις του παραθύρου αλλάζουν.
	//Το set πρέπει να γίνει στη main (????). Έχουμε μια συνάρτηση (είναι ένα callback, το οποίο δεν το χουμε φτιάξει
	// και θα πρέπει να το ορίσουμε. Είναι το callback που καλείται όταν κάνω resize το παράθυρο (check-->SGG:callbacks, setResizeFunction).

	void setDebugMode(bool d) { debug_mode = d; }	
	bool getDebugMode() const { return debug_mode; }	

	//capture pause time
	void setPauseTime(float t) { remainingTime = t; }		//remainingTime
	float getPauseTime() const { return remainingTime; }	//remainingTime

	//capture start time
	void setStartime(float t) { remainingTime = t; }		//remainingTime
	float getStartTime() const { return remainingTime; }	//remainingTime


	void setTime(float t) { remainingTime = t; }
	float getTime() const { return remainingTime; }


	Game();
	~Game();
};
