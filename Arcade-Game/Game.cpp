#include "game.h"
#include "graphics.h"
#include <stdio.h>		

using namespace std;

void Game::checkMeteorite()
{
	if (meteorite && !meteorite->isActive())
	{
		delete meteorite;		
		meteorite = nullptr;
	}
}

void Game::checkBullet(Bullet*& sh_bull)
{
	if (sh_bull && !sh_bull->isActive())
	{
		delete sh_bull;		
		sh_bull = nullptr;
	}
}


void Game::checkAlien() {
	if (!aliens.empty()) {
		for (int i = 0; aliens.size(); i++) {
			for (list_it = aliens[i].begin(); list_it != aliens[i].end(); list_it++) {
				if (*list_it && !(*list_it)->isActive()) {			//** FIX   -->  ìå ôá collision alien-plBullet êáé alien-bunker.
					delete* list_it;
					*list_it = nullptr;

					// erase form list ++ from vector.
				}
			}
		} //end of vector for
	} //end of list for.

	aliens.clear();		//** CHECK.
}



void Game::spawnMeteorite()		
{
	if (!meteorite)
	{
		meteorite = new Meteorite(*this);	
													
													
	}
}

void Game::shootBullet(Bullet*& sh_bullet, float sh_pos_x, float sh_pos_y, bool sh)		// pass pointer by reference (it's GameObject because of checkCollision methods).
{
	if (!sh_bullet)
	{
		graphics::playSound(std::string(ASSET_PATH) + "music\\Gun1.mp3", 0.5f, false);

		sh_bullet = new Bullet(*this, sh_pos_x, sh_pos_y);				
		reinterpret_cast<Bullet*>(sh_bullet)->set_move_to_east(sh);		
	}
}


bool Game::checkCollision_Cir_Cir(Disk& disk_1, Disk& disk_2)		// intersection test circle-circle.		
{
	float Dx = disk_1.cx - disk_2.cx;
	float Dy = disk_1.cy - disk_2.cy;

	return (sqrt(Dx * Dx + Dy * Dy) <= disk_1.radius + disk_2.radius);		
}

bool Game::checkCollision_Rec_Cir(Rectangle& rect, Disk& disk)		// intersection test rectangle-circle.
{
	// find rectangle's closest point (rec_x, rec_y) to circle's center (cx,cy).
	// (x1,y1) is the bottom left rec's corner. (x2, y2) is the top right rec's corner.

	float Dx = disk.cx - std::max<float>(rect.topLeftX, std::min<float>(disk.cx, rect.topLeftX + rect.rec_width));
	float Dy = disk.cy - std::max<float>(rect.topLeftY, std::min<float>(disk.cy, rect.topLeftY + rect.rec_height));		
	return (sqrt(Dx * Dx + Dy * Dy) <= disk.radius);
}

bool Game::checkCollision_Rec_Rec(Rectangle& rec1, Rectangle& rec2)		// intersection test rectangle-rectangle.
{
	// (x1,y1) is the bottom left rec's corner. (x2, y2) is the top right rec's corner.

	if ((rec2.botRightY < rec1.topLeftY || rec2.topLeftY > rec1.botRightY)			// If one rectangle is above/below the other
		|| (rec2.botRightX < rec1.topLeftX || rec2.topLeftX > rec1.botRightX))		// or on right/left side of the other
	{																					// -> the rectangles don't intersect.		// <--	** åîÞãçóç (óõíô/íåò êáìâÜ).
		return false;																	
	}
	else
		return true;
}



///////////////////////////////////////////////////** Update screen methods **////////////////////////////////////////////////////////////////////
void Game::updateStartScreen()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);	
	if (ms.button_left_pressed || graphics::getKeyState(graphics::SCANCODE_RETURN))		
	{								
		status = STATUS_PLAYING;	
		graphics::playMusic(std::string(ASSET_PATH) + "music\\playing-music.mp3", 0.5f, true, 4000);
	}
}


void Game::updateLevelScreen()
{
	if (!player_initialized && !aliens_initialized &&		
		!bunkers_initialized && !plBullet_initialized && 	graphics::getGlobalTime() > 1000)		//diorthosi (giati meta apo kathe kinisi ton epanefere sto kentro): kanoume ena state.
	{

		player = new Player(*this, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 70.0f);		// png: 377.0f/445.0f
		player_initialized = true;		

		bunkers.reserve(3);
		for (int i = 0; i < 3; i++) {
			Bunker* bunk = new Bunker(*this, 250, 100.0f + 150 * i, 100.0f);		// png: 66.0f/140.0f
			bunkers.push_back(bunk);
		}
		bunkers_initialized = true;

		aliens.reserve(3);					//3 theseis vector

		for (int i = 0; i < 7; i++) {
			Alien* alienc1 = new Alien(*this, 900, 45 + i * 65);
			alienCol1.push_back(alienc1);
		}
		for (int i = 0; i < 7; i++) {
			Alien* alienc2 = new Alien(*this, 800, 45 + i * 65);
			alienCol2.push_back(alienc2);
		}
		for (int i = 0; i < 7; i++) {
			Alien* alienc3 = new Alien(*this, 700, 45 + i * 65);
			alienCol1.push_back(alienc3);
		}

		aliens.push_back(alienCol1);
		aliens.push_back(alienCol2);
		aliens.push_back(alienCol3);

		aliens_initialized = true;
		
	}
	/* Collision hulls. */
	if (player) 
	{
		playerHull = player->getCollisionHull(0.533f);		// player's size = 60.0f.		//** FIX: put variable in the class.
	}
	if(meteorite)
	{
		meteoriteHull = meteorite->getCollisionHull(0.42f);
	}
	if (playerBullet) 
	{
		float pl_bull_PNG_dims_ratio = (playerBullet->get_draw_gobj_png()).get_png_dims_ratio();
		playerBulletHull = playerBullet->getCollisionHull(pl_bull_PNG_dims_ratio, 1.0f);
	}
	if (alienBullet)
	{
		float al_bull_PNG_dims_ratio = (alienBullet->get_draw_gobj_png()).get_png_dims_ratio();
		alienBulletHull = alienBullet->getCollisionHull(al_bull_PNG_dims_ratio, 1.0f);
	}
	
	for (int i = 0; i < bunkers.size(); i++) {
		if (bunkers[i]) {
			bunkers[i]->update();

			float bun_PNG_dims_ratio = bunkers[i]->get_draw_gobj_png().get_png_dims_ratio();
			bunkerHull = bunkers[i]->getCollisionHull(bun_PNG_dims_ratio, 1.0f);

			// Check collisions for the bunkers. //
			if (playerBullet)		/* Bunker - player bullet collision. */
			{
				if (checkCollision_Rec_Rec(playerBulletHull, bunkerHull))
				{
					bunkers[i]->drainLife(0.1f);

					delete playerBullet;
					playerBullet = nullptr;
				}
			}
			if (alienBullet)		/* Bunker - alien bullet collision. */
			{
				if (checkCollision_Rec_Rec(alienBulletHull, bunkerHull))
				{
					// ++ explosion.
					bunkers[i]->drainLife(0.1f);

					delete alienBullet;
					alienBullet = nullptr;
				}
			}
			if (meteorite)			/* Bunker - meteorite collision. */
			{
				if (checkCollision_Rec_Cir(bunkerHull, meteoriteHull))
				{
					explosion = new Explosion(*this, meteorite->getPosX(), meteorite->getPosY());		// png: 512.0f / 512.0f
					//explosion_initialized = true;

					bunkers[i]->drainLife(0.2f);

					delete meteorite;
					meteorite = nullptr;
				}
			}
			if (player)				/* Bunker - player collision. */
			{
				//player->checkStopByBunker(bunkers[i]);			//** FIX
				if (checkCollision_Rec_Cir(bunkerHull, playerHull))
				{
					graphics::playSound(std::string(ASSET_PATH) + "music\\smash-sound.mp3", 0.3f, false);
				}
			}

			if (!bunkers[i]->isActive())
			{
				graphics::playMusic(std::string(ASSET_PATH) + "music\\Bomb.mp3", 0.5f, false, 4000);

				delete bunkers[i];		//óâÞíåé ôï ðåñéå÷üìåíï ôïõ pointer.	//OK
				bunkers[i] = nullptr;

				// ++ erase.
			}
		}
	}
	
	/* Update and check collisions for the aliens' group. */
	for (int i = 0; i < aliens.size(); i++) {
		for (list_it = aliens[i].begin(); list_it != aliens[i].end(); list_it++) {
			if (*list_it) {

				if (graphics::getGlobalTime() > 13000)		//** CHECK (delay).
				{
					(*list_it)->update();
				}

				alienHull = (*list_it)->getCollisionHull(0.45f);

				if (playerBullet)		/* Player bullet - alien collision. */
				{
					if (checkCollision_Rec_Cir(playerBulletHull, alienHull))
					{
						delete playerBullet;			
						playerBullet = nullptr;
						delete* list_it;
						*list_it = nullptr;

						// ++ erase from list. ++ (ðéï êÜôù) erase from vector (áð' ôï ôÝëïò).

						alienKills++;
					}
				}

			}
		} //end of list for.
	} //end of vector for.

	if (player)				
	{
		player->update();	

		if (meteorite)		
		{
			if (checkCollision_Cir_Cir(playerHull, meteoriteHull))		
			{
				explosion = new Explosion(*this, meteorite->getPosX(), meteorite->getPosY());		
				explosion_initialized = true;

				player->drainLife(0.1f);

				delete meteorite;
				meteorite = nullptr;
			}
		}

		if (alienBullet)	
		{
			if (checkCollision_Rec_Cir(alienBulletHull, playerHull))
			{
				// ++
				player->drainLife(0.08f);

				delete alienBullet;
				alienBullet = nullptr;
			}
		}

		if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		{
			shootBullet(playerBullet, player->getPosX() + player->getSize() / 2 + 5, player->getPosY(), true);		
		}
		if (graphics::getKeyState(graphics::SCANCODE_F))	
		{
			status = STATUS_PAUSE;
			graphics::playMusic(std::string(ASSET_PATH) + "music\\start-pause-music.mp3", 0.5f, true, 4000);

		}
		if (!player->isActive())		
		{
			status = STATUS_GAME_OVER;		
			graphics::playMusic(std::string(ASSET_PATH) + "music\\gameOver-music.mp3", 0.5f, true, 4000);
		}

	}

	if(meteorite)			
	{	
		if (graphics::getGlobalTime() > 11000)
		{
			meteorite->update();
		}
		
		if (!player)		
		{
			status = STATUS_GAME_OVER;
		}
	}

	if(playerBullet) 
	{
		playerBullet->update();		

		if (meteorite)		
		{
			if (checkCollision_Rec_Cir(playerBulletHull, meteoriteHull))
			{
			
				explosion = new Explosion(*this, meteorite->getPosX(), meteorite->getPosY());

				delete playerBullet;
				playerBullet = nullptr;
				delete meteorite;
				meteorite = nullptr;

				meteoKills++;
			}
		}
		if (alienBullet)	
		{
			if (checkCollision_Rec_Rec(alienBulletHull, playerBulletHull))
			{
				// ++ explosion.
				delete alienBullet;
				alienBullet = nullptr;
				delete playerBullet;
				playerBullet = nullptr;
			}
		}
	}	

	if(alienBullet)
	{
		alienBullet->update();		
		if (playerBullet)
		{
			checkAlien();		
		}
	}
	
	if(explosion)
		explosion->update();		

	checkMeteorite();
	checkBullet(alienBullet);
	checkBullet(playerBullet);
	spawnMeteorite();
}

void Game::updateEndScreen()		
{
	aliens_initialized = false;		
	player_initialized = false;		
	bunkers_initialized = false;	
	plBullet_initialized = false;


	if (graphics::getKeyState(graphics::SCANCODE_1))	
	{

		status = STATUS_START;			
		graphics::playMusic(std::string(ASSET_PATH) + "music\\start-pause-music.mp3", 0.5f, true, 4000);

		score = 0;
		meteoKills = 0;
		gameOverTime = 0.0f;
	}
}

void Game::updatePauseScreen()		
{
	if (graphics::getKeyState(graphics::SCANCODE_1))
	{
		
		status = STATUS_PLAYING;
		graphics::playMusic(std::string(ASSET_PATH) + "music\\gameOver-music.mp3", 0.5f, true, 4000);
	}
	if (graphics::getKeyState(graphics::SCANCODE_2))
	{
		status = STATUS_GAME_OVER;
		graphics::playMusic(std::string(ASSET_PATH) + "music\\gameOver-music.mp3", 0.5f, true, 4000);
	}
	
}


////////////////////////////////////////////////////////////** Draw screen methods **////////////////////////////////////////////////////////////////////////


void Game::drawStartScreen()
{
	/*Draw start screen background.*/
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "backgrounds\\space.png";
	br.outline_opacity = 0.0f;								
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 /*+offset*/, CANVAS_WIDTH, CANVAS_HEIGHT, br);	

	char info[40];													
	sprintf_s(info, "Press ENTER to start");						
	graphics::drawText(CANVAS_WIDTH / 2 - 120 /*FIX HERE*/, CANVAS_HEIGHT / 2, 30, info, br);
												
												
	br.texture = "";				
	
	graphics::MouseState ms;
	graphics::getMouseState(ms);	
	graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10.0f, br);
}

void Game::drawLevelScreen()
{
	

	graphics::Brush br;	


	br.texture = std::string(ASSET_PATH) + "backgrounds\\mars1.png";		
	br.outline_opacity = 0.0f;															
	graphics::drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_WIDTH * (500.0f/800.0f), br);	

	/* Draw bunkers. */
	for (int i = 0; i < bunkers.size(); i++) {
		if (bunkers[i]) {
			bunkers[i]->set_draw_gobj_png(bunkerPNG);
			bunkers[i]->draw();		
		}
	}

	/* Draw aliens' group. */
	for (int i = 0; i < aliens.size(); i++) {
		for (list_it = aliens[i].begin(); list_it != aliens[i].end(); list_it++) {
			if (*list_it) {
				(*list_it)->set_draw_gobj_png(alienPNG);		//** CHECK
				(*list_it)->draw();
			}
		} //end of list for.
	} //end of vector for.

	if (player)
	{
		player->set_draw_gobj_png(playerPNG);
		player->draw();
	}	
	if (playerBullet)
	{
		playerBullet->set_draw_gobj_png(playerBulletPNG);
		playerBullet->draw();
	}
	if (alienBullet)
	{
		alienBullet->set_draw_gobj_png(alienBulletPNG);
		alienBullet->draw();
	}
	if (meteorite)
	{
		meteorite->set_draw_gobj_png(meteoritePNG);
		meteorite->draw();
	}
	if (explosion)
	{
		explosion->set_draw_gobj_png(explosionPNG);
		explosion->draw();		// <<---
	}
		

	if (player)
	{
	
		if (meteoKills == 0 && alienKills == 0) {
			score = 0;
		}
		else if (player->getRemainingLife() != 0.0f) {
			score = (400 * alienKills) + (300 * meteoKills) + (150 * player->getRemainingLife());
		}
		else 
		{
			score = 400 * alienKills + 300 * meteoKills; 
		}
	}

	float player_life = (player ? player->getRemainingLife() : 0.0f);

	br.outline_opacity = 0.0f;		
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";

	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;	
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.gradient = true;						
	br.gradient_dir_u = 1.0f;				
	br.gradient_dir_v = 0.0f;				
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);
	br.outline_opacity = 0.5f;
	br.gradient = false;
	br.fill_opacity = 0.0f;			
	graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 20, br);

}

void Game::drawEndScreen()		
{
			
	graphics::Brush br;
									
	br.texture = std::string(ASSET_PATH) + "backgrounds\\gameover1.png";		
	br.outline_opacity = 0.0f;												
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 /*+offset*/, CANVAS_WIDTH, CANVAS_WIDTH * 0.473f, br);	

	char info[40];										
	sprintf_s(info, "GAME OVER");					
	graphics::drawText(370 , CANVAS_HEIGHT / 2, 60, info, br);

	br.fill_color[0] = 0.7f;				
	br.fill_color[1] = 0.8f;
	br.fill_color[2] = 1.0f;
	sprintf_s(info, "Press 1 to try again");		
	graphics::drawText(50, 455, 20, info, br);

	br.fill_color[0] = 0.7f;				
	br.fill_color[1] = 0.8f;
	br.fill_color[2] = 1.0f;
	sprintf_s(info, "Press ESC to exit");														
	graphics::drawText(50 , 475, 20, info, br);

	sprintf_s(info, "Total Score:%d", score);	
													
	graphics::drawText(800, 30 , 20, info, br);
}

void Game::drawPauseScreen()		
{
	/*Draw end screen background.*/
	graphics::Brush br;
									
	br.texture = std::string(ASSET_PATH) + "backgrounds\\pause.png";		
	br.outline_opacity = 0.0f;												
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH * 0.473f, br);	

	char info[40];
	br.fill_color[0] = 0.0f;			
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	sprintf_s(info, "PAUSED GAME");
	graphics::drawText(370, CANVAS_HEIGHT / 2 +20, 60, info, br);		
	br.fill_color[0] = 1.0f;			
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	sprintf_s(info, "Press 1 to resume game");		
	graphics::drawText(50, 455, 20, info, br);
	sprintf_s(info, "Press 2 to exit");		
	graphics::drawText(50, 475, 20, info, br);
}




float Game::window2canvasX(float x)		
{
	return x * CANVAS_WIDTH / (float)window_width ;
}

float Game::window2canvasY(float y)		
{
	return y * CANVAS_HEIGHT / (float)window_height;
}



/////////////////////////////////////////////////////////** Update - draw - init methods **/////////////////////////////////////////////////////////////////

void Game::update()		
{
	if (status == STATUS_START)
	{
		updateStartScreen();		
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen();	
	}
	else if (status == STATUS_PAUSE)
	{
		updatePauseScreen();
	}
	else if (status == STATUS_GAME_OVER)
	{
		updateEndScreen();
	}
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else if (status == STATUS_PAUSE)
	{
		drawPauseScreen();
	}
	else if (status == STATUS_GAME_OVER)
	{
		drawEndScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "SF Theramin Gothic Condensed.ttf");
	musicInit();		
}

void Game::musicInit(/*status_t status*/) {		

	if ((status == STATUS_PAUSE) || (status == STATUS_START)) {
		graphics::playMusic(std::string(ASSET_PATH) + "music\\start-pause-music.mp3", 0.5f, true, 4000);
	}
	else if (status == STATUS_PLAYING) {
		graphics::playMusic(std::string(ASSET_PATH) + "music\\playing-music.mp3", 0.5f, true, 4000); 
	}
	else if (status == STATUS_GAME_OVER) {
		graphics::playMusic(std::string(ASSET_PATH) + "music\\gameOver-music.mp3", 0.5f, true, 4000);		
	}
}



///////////////////////////////////////////////////** Constructor - Destructor **///////////////////////////////////////////////////

Game::Game()	
{
}

Game::~Game()		
{
	if (player)		
	{
		delete player;		
	}

	if(playerBullet) {		
		delete playerBullet;
	}

	if(alienBullet) {		
		delete alienBullet;
	}

	for (int i = 0; i < 3; i++) {		
		if (bunkers[i]) {
			delete bunkers[i];		
		}
	}

	if (explosion) {             
		delete explosion;
	}

	if (meteorite) {              
		delete meteorite;
	}
}
