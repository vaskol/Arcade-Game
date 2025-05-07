#include "game.h"
#include "graphics.h"
//#include "config.h"	

#include <stdio.h>		// <--


using namespace std;



/* TO-DO: -ο μετεωρ να προκαλεί ζημιά στο σκάφος ανάλογα με το μέγεθός του και το πόσο πολύ/λίγο έχει βρει/χτυπήσει το σκάφος.
		  -FIX τον κύκλο στο ποντίκι, όταν μεγαλ το παράθυρο.
*/

/*
void Game::checkActive(GameObject*& game_obj)		// pass pointer by reference. 
{
	if (game_obj && !game_obj->isActive())
	{
		delete game_obj;		//σβήνει το περιεχόμενο του pointer.
		game_obj = nullptr;
	}
}*/

void Game::checkMeteorite()
{
	if (meteorite && !meteorite->isActive())
	{
		delete meteorite;		//σβήνει το περιεχόμενο του pointer.
		meteorite = nullptr;
	}
}

void Game::checkBullet(Bullet*& sh_bull)
{
	if (sh_bull && !sh_bull->isActive())
	{
		delete sh_bull;		//σβήνει το περιεχόμενο του pointer.
		sh_bull = nullptr;
	}
}

/*
void Game::checkBunker()			// <--
{
	for (int i = 0; i < bunkers.size(); i++) {
		if (bunkers[i] && !bunkers[i]->isActive())		// <-- μέσα στο for του στην updateLevelScreen.
		{
			graphics::playMusic(std::string(ASSET_PATH) + "music\\Bomb.mp3", 0.5f, false, 4000);

			delete bunkers[i];		//σβήνει το περιεχόμενο του pointer.	//OK
			bunkers[i] = nullptr;
		}
	}
}*/

void Game::checkAlien() {
	if (!aliens.empty()) {
		for (int i = 0; aliens.size(); i++) {
			for (list_it = aliens[i].begin(); list_it != aliens[i].end(); list_it++) {
				if (*list_it && !(*list_it)->isActive()) {			//** FIX   -->  με τα collision alien-plBullet και alien-bunker.
					delete* list_it;
					*list_it = nullptr;

					// erase form list ++ from vector.
				}
			}
		} //end of vector for
	} //end of list for.

	aliens.clear();		//** CHECK.
}



void Game::spawnMeteorite()		//Ο μετεωρ ξεκινά από μια θέση εκτός της οθόνης (π.χ. δεξιά->κατά πάνω μας) (προς και από οποιαδήποτε κατ/ση). Τώρα ΦΤΙΑΧΝΩ τον μετεωρ (το ΠΑΙΧΝΙΔΙ φτιάχνει τον μετεωρ). Μέχρι τώρα ειχα τον POINTER.
{
	if (!meteorite)
	{
		meteorite = new Meteorite(*this);	// png dimensions: 696*464.	 464.0f / 696.0f
													//this???	//Αν είχε να ελέγξει κι άλλες συνθήκες, θα έπρεπε να το κάνει εδώ πέρα. Οποιαδήποτε λογική αφορά τους 
													// εχθρούς, ας πάει σε μία και μοναδική συνάρτ., να μη βλέπω εγώ τίποτα απ' έξω.
	}
}

void Game::shootBullet(Bullet*& sh_bullet, float sh_pos_x, float sh_pos_y, bool sh)		// pass pointer by reference (it's GameObject because of checkCollision methods).
{
	if (!sh_bullet)
	{
		graphics::playSound(std::string(ASSET_PATH) + "music\\Gun1.mp3", 0.5f, false);

		sh_bullet = new Bullet(*this, sh_pos_x, sh_pos_y);				//** FIX size->draw()	//size=30.0f -> init().
		reinterpret_cast<Bullet*>(sh_bullet)->set_move_to_east(sh);		//** CHECK !!!
	}
}

//void Game::createExplosion() //thelo oxi mono meteorites posx kai y alla kai bunkers
//{
//	if (!explosion)
//	{
//		
//		
//	}
//}
//
//void Game::shootBullet()
//{
//	
//	if (!alienBullet)
//	{
//		alienBullet = new Bullet(*this, alien->getPosX() + alien->getSize() / 2 + 5, alien->getPosY());		//** FIX size->draw()	//size=30.0f -> init().
//	}
//}



/*void Game::collisionDamage(GameObject*& game_obj)	//************* CONTINUE HERE <<--- //
{
	if (game_obj->get_one_collision_dead() == true)		//** CHECK-FIX.
	{
		//!game_obj->isActive();
		game_obj->drainLife(1.0f);		// Στην drainLife(): active=life;
	}
	else
	{
		game_obj->drainLife(0.1f);
	}
}*/

/*bool Game::checkCollision(GameObject* game_obj_1, GameObject* game_obj_2)
{
	if (!game_obj_1 || !game_obj_2)
	{
		return false;
	}

	Shape d1 = game_obj_1->getCollisionHull();		// d1 me d3
	Shape d3 = game_obj_2->getCollisionHull();

	float dx = d1.cx - d3.cx;
	float dy = d1.cy - d3.cy;
	//prepei na vgalo to collision me ton paikti kai ton meteoriti tora exo sferes

	if (sqrt(dx * dx + dy * dy) < d1.radius + d3.radius)		// <<----
	{
		collisionDamage(game_obj_1);		//************* CONTINUE HERE //
		collisionDamage(game_obj_2);
		return true;
	}
	else
		return false;
}*/

bool Game::checkCollision_Cir_Cir(Disk& disk_1, Disk& disk_2)		// intersection test circle-circle.		// OK
{
	float Dx = disk_1.cx - disk_2.cx;
	float Dy = disk_1.cy - disk_2.cy;

	return (sqrt(Dx * Dx + Dy * Dy) <= disk_1.radius + disk_2.radius);		// <--
}

bool Game::checkCollision_Rec_Cir(Rectangle& rect, Disk& disk)		// intersection test rectangle-circle.
{
	// find rectangle's closest point (rec_x, rec_y) to circle's center (cx,cy).
	// (x1,y1) is the bottom left rec's corner. (x2, y2) is the top right rec's corner.

	float Dx = disk.cx - std::max<float>(rect.topLeftX, std::min<float>(disk.cx, rect.topLeftX + rect.rec_width));
	float Dy = disk.cy - std::max<float>(rect.topLeftY, std::min<float>(disk.cy, rect.topLeftY + rect.rec_height));		// <--	** εξήγηση (συντ/νες καμβά).
	return (sqrt(Dx * Dx + Dy * Dy) <= disk.radius);
}

bool Game::checkCollision_Rec_Rec(Rectangle& rec1, Rectangle& rec2)		// intersection test rectangle-rectangle.
{
	// (x1,y1) is the bottom left rec's corner. (x2, y2) is the top right rec's corner.

	if ((rec2.botRightY < rec1.topLeftY || rec2.topLeftY > rec1.botRightY)			// If one rectangle is above/below the other
		|| (rec2.botRightX < rec1.topLeftX || rec2.topLeftX > rec1.botRightX))		// or on right/left side of the other
	{																					// -> the rectangles don't intersect.		// <--	** εξήγηση (συντ/νες καμβά).
		return false;																	
	}
	else
		return true;
}



///////////////////////////////////////////////////** Update screen methods **////////////////////////////////////////////////////////////////////
void Game::updateStartScreen()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);	//Θέλουμε να κάνουμε να αλλάζει η οθόνη και μ' ένα κλικ του ποντικιού 
	if (ms.button_left_pressed || graphics::getKeyState(graphics::SCANCODE_RETURN))		//(αν έχω κάνει "press" και "release" το ποντίκι, "press" βασικά) ή RETURN -> ENTER.
	{								// [αν θέλουμε να μπαίνει σε full screen (??), ας μπαίνει σε full screen (??)]
		status = STATUS_PLAYING;	 //** CHECK
		graphics::playMusic(std::string(ASSET_PATH) + "music\\playing-music.mp3", 0.5f, true, 4000);
	}
}

//OSO PERNAEI O XRONOS NA ALLAZOUN THESI OI EKSWGIOINOI KAI OI METEO NA PANE PIO ARGA
void Game::updateLevelScreen()
{
	//*** Στη φάση που το παιχνίδι παίζεται PREPEI NA EINAI KAI TO SMINOS ALIENS ENERGO KAI O PAIXTHS. ***//
	if (!player_initialized && !aliens_initialized &&		/*!meteorite_initialized && */
		!bunkers_initialized && !plBullet_initialized && /*!alBullet_initialized &&*/	graphics::getGlobalTime() > 1000 /* !!! */)		//diorthosi (giati meta apo kathe kinisi ton epanefere sto kentro): kanoume ena state.
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
		/*for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++) {
				Alien* alienc1 = new Alien(*this, 350 + i * 100, 100 + j * 30);
				alienListCol.push_back(alienc1);
			}
			aliens.push_back(alienListCol);
		}*/
	}

	/*if ( checkCollision_Rec_Cir(playerBullet, alien) || checkCollision_Rec_Cir(playerBullet, meteorite) )
		//xoris true
	{
		kills++;
	}*/
	
	/*if (checkCollision_Rec_Cir(playerBullet, meteorite))
	{
		meteoKills++;
	}*/

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

				delete bunkers[i];		//σβήνει το περιεχόμενο του pointer.	//OK
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

						// ++ erase from list. ++ (πιο κάτω) erase from vector (απ' το τέλος).

						alienKills++;
					}
				}

				// TO-DO: /* alien - bunker collision. */
			}
		} //end of list for.
	} //end of vector for.

	if (player)				//Efoson yparxei o paiktis (An yparxei o player pointer), na tou emimerono tin katastasi tou.
	{
		player->update();	//Εδώ κινείται με τα πλήκτρα.

		if (meteorite)		/* Player - meteorite collision. */
		{
			if (checkCollision_Cir_Cir(playerHull, meteoriteHull))		//Collision μεταξύ παίκτη και μετεωρίτη: παίκτης->χάνει ζωή, μετεωρίτης->delete.
			{
				explosion = new Explosion(*this, meteorite->getPosX(), meteorite->getPosY());		// png: 512.0f / 512.0f
				explosion_initialized = true;

				player->drainLife(0.1f);

				delete meteorite;
				meteorite = nullptr;
			}
		}

		if (alienBullet)	/* Player - alien bullet collision. */
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
			shootBullet(playerBullet, player->getPosX() + player->getSize() / 2 + 5, player->getPosY(), true);		// png: 500.0f/500.0f		//πυροβολεί (δημ νέο αντικ σφαίρας) με το SPACE.
		}
		if (graphics::getKeyState(graphics::SCANCODE_F))	//αν πατήσει το F -> STATUS PAUSE.
		{
			status = STATUS_PAUSE;
			graphics::playMusic(std::string(ASSET_PATH) + "music\\start-pause-music.mp3", 0.5f, true, 4000);
			//pause = graphics::getDeltaTime()/1000;
		}
		if (!player->isActive())		//** CHECK
		{
			status = STATUS_GAME_OVER;		//Αν πεθάνει ο παίκτης --> με πάει σε άλλο STATUS.
			graphics::playMusic(std::string(ASSET_PATH) + "music\\gameOver-music.mp3", 0.5f, true, 4000);
			/*
				//player_initialized = false;
					//Για να δημιουργ. μετά καινούριο αντικ., αλλιώς:
					// 1) συνεχ. στη levelScreen με την εναπομ. ζωή (NOT FIXED HERE!!->δεν ισχύει αν πάμε για κάποιο λόγο κατευθείαν στο GAME OVER, πριν τελειώσει η ζωή)
					// 2) αν δεν έχει ζωή-> πάει στο GAME OVER!! (FIXED!!)
					*/
		}

		//** FIX: μετά το play screen πάει απευθείας στο Game Over (κάπως με reset ή/και με το game over time)
		//termatizei to paixnidi otan o pektis pethainei H otan o xronos einai ligoteros apo ena lepto H otan pethainoun oloi oi aliens
		//if ((player->getRemainingLife() <= 0.0f) || (graphics::getGlobalTime() >= 60000))/* ||(!aliens)*/ {
			//gameOverTime = graphics::getGlobalTime();
			//status = STATUS_GAME_OVER;		//Αν πεθάνει ο παίκτης --> με πάει σε άλλο STATUS.
			//musicInit();
		//}
	}

	//if (alien)	//**FIX: Αργεί να εμφανιστεί η PLAYING SCREEN (άσπρη). Στο μεταξύ κινείται ο alien (και οι μετεωρίτες).	/* Demo */
	//{
		//if(graphics::getGlobalTime() > 11000)
		//{
			//alien->update();
			/*if (graphics::getGlobalTime() > 12000)		//**FIX: όταν φεύγει η πρώτη σφαίρα ΚΟΛΛΑΕΙ.
			{
				//for (int i=0; i<3; i++)		//**FIX
				//shootBullet(alienBullet, alien->getPosX() - alien->getSize()/2 - 5, alien->getPosY(), false, 400.0f/1047.0f);		// alien bullet moves from east to west.
			}*/
			/*if (graphics::getGlobalTime() > 13000)		//**FIX: όταν φεύγει η πρώτη σφαίρα ΚΟΛΛΑΕΙ.
			{
				//for (int i=0; i<3; i++)		//**FIX
				shootBullet(alienBullet, alien->getPosX() - alien->getSize() / 2 - 5, alien->getPosY(), false);		// alien bullet moves from east to west.
			}*/
		//}
	//}

	//if (aliens)	//**FIX: Αργεί να εμφανιστεί η PLAYING SCREEN (άσπρη). Στο μεταξύ κινείται ο alien (και οι μετεωρίτες).	/* Demo */
	//{
	//	if (graphics::getGlobalTime() > 11000)
	//	{
	//		aliens->update();
	//		/*if (graphics::getGlobalTime() > 12000)		//**FIX: όταν φεύγει η πρώτη σφαίρα ΚΟΛΛΑΕΙ.
	//		{
	//			//for (int i=0; i<3; i++)		//**FIX
	//			//shootBullet(alienBullet, alien->getPosX() - alien->getSize()/2 - 5, alien->getPosY(), false, 400.0f/1047.0f);		// alien bullet moves from east to west.
	//		}*/
	//		/*if (graphics::getGlobalTime() > 13000)		//**FIX: όταν φεύγει η πρώτη σφαίρα ΚΟΛΛΑΕΙ.
	//		{
	//			//for (int i=0; i<3; i++)		//**FIX
	//			shootBullet(alienBullet, alien->getPosX() - alien->getSize() / 2 - 5, alien->getPosY(), false);		// alien bullet moves from east to west.
	//		}*/
	//	}
	//}

	if(meteorite)			//**FIX		//Efoson yparxei o meteorite (An yparxei o meteorite pointer), na tou emimerono tin katastasi tou.
	{	
		if (graphics::getGlobalTime() > 11000)
		{
			meteorite->update();
		}
		/*if (player)
		{
			/*if (checkCollision_Cir_Cir(*player, *meteorite))		//Collision μεταξύ παίκτη και μετεωρίτη: παίκτης->χάνει ζωή, μετεωρίτης->delete.
			{
				explosion = new Explosion(*this, meteorite->getPosX(), meteorite->getPosY(), 512.0f / 512.0f);
				explosion_initialized = true;

				player->drainLife(0.1f);

				delete meteorite;
				meteorite = nullptr;
			}*/
		//}*/
		if (!player)		// <--
		{
			status = STATUS_GAME_OVER;
		}
	}

	if(playerBullet) 
	{
		playerBullet->update();		// <<---

		if (meteorite)		/* Player bullet - meteorite collision. */
		{
			if (checkCollision_Rec_Cir(playerBulletHull, meteoriteHull))
			{
				// ++ delete expl sto telos edo.
				explosion = new Explosion(*this, meteorite->getPosX(), meteorite->getPosY());
				//explosion_initialized = true;

				delete playerBullet;
				playerBullet = nullptr;
				delete meteorite;
				meteorite = nullptr;

				meteoKills++;
			}
		}
		if (alienBullet)	/* Player bullet - alien bullet collision. */
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
		alienBullet->update();		// <<---
		if (playerBullet)
		{
			/*if (checkCollision_Rec_Rec(*alienBullet, *playerBullet))
			{
				// ++ explosion.
				delete alienBullet;
				alienBullet = nullptr;
				delete playerBullet;
				playerBullet = nullptr;
			}*/

			checkAlien();		// <--
		}
	}
	
	if(explosion)
		explosion->update();		// <<---

	//EDW KANEI UPDATE GIA NA PROXWRAEI H BULLET SE SUNEXOMENH ROI KATHOS PATAW TO F , DEN EINAI SWSTH LOGIKI
	/*for (int i = 0; i < 10; i++) {		//** Demo (FIX) [10 σφαίρες ??]
		if (playerBullet)
			playerBullet->update();
	}*/


	//checkActive(player);
	//checkActive(meteorite);
	//checkActive(playerBullet);
	//checkActive(alien);
	//checkActive(alienBullet);
	checkMeteorite();
	checkBullet(alienBullet);
	checkBullet(playerBullet);
	//checkBunker();
	//checkExplosion();

	spawnMeteorite();

	/* for TEST: αν τύχει να πάμε σε GAME OVER, χωρίς να πεθάνει ο παίκτης */
	//if (graphics::getKeyState(graphics::SCANCODE_0))		/* (μπορ να το κάνουμε να γίνεται όταν δebug_mode=0) */
	//{
	//	status = STATUS_GAME_OVER;
	//}
}

void Game::updateEndScreen()		//maybe doesn't need.
{
	aliens_initialized = false;		
	player_initialized = false;		
	bunkers_initialized = false;	
	plBullet_initialized = false;
	//alBullet_initialized = false;

	if (graphics::getKeyState(graphics::SCANCODE_1))	//1 -> START.	/* FIX: αν ο παίκτης έχει πεθάνει: από τη START SCREEN -> κατευθείαν GAME OVER */
	{
		//graphics::stopMusic(/*4000*/);
		status = STATUS_START;			//** εδώ κάτι με reset.
		graphics::playMusic(std::string(ASSET_PATH) + "music\\start-pause-music.mp3", 0.5f, true, 4000);

		score = 0;
		meteoKills = 0;
		gameOverTime = 0.0f;
	}
}

void Game::updatePauseScreen()		/* FIX HERE */
{
	//thelo na epistrepsei stin palia katastasi to paixnidi prin to pause

	//musicInit(/*status*/);
	if (graphics::getKeyState(graphics::SCANCODE_1))
	{
		//startplaying= graphics::getDeltaTime() / 1000;
		status = STATUS_PLAYING;
		graphics::playMusic(std::string(ASSET_PATH) + "music\\gameOver-music.mp3", 0.5f, true, 4000);
	}
	if (graphics::getKeyState(graphics::SCANCODE_2))
	{
		status = STATUS_GAME_OVER;
		graphics::playMusic(std::string(ASSET_PATH) + "music\\gameOver-music.mp3", 0.5f, true, 4000);
	}
	//drawLevelScreen();
}


////////////////////////////////////////////////////////////** Draw screen methods **////////////////////////////////////////////////////////////////////////

//** USE new draw methods.		<<----

void Game::drawStartScreen()
{
	/*Draw start screen background.*/
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "backgrounds\\space.png";
	br.outline_opacity = 0.0f;								//to disappear the white line at the perimeter.
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 /*+offset*/, CANVAS_WIDTH, CANVAS_HEIGHT, br);	//png dimensions: 720*480 pixels (CANVAS_WIDTH/CANVAS_HEIGHT=1.5)

	char info[40];													//αντί για string βάζω buffer, για να γλιτ λίγο χώρο.
	sprintf_s(info, "Press ENTER to start");						//όλες οι μονάδες που χρησ/με -> σε μονάδες καμβά.
	graphics::drawText(CANVAS_WIDTH / 2 - 120 /*FIX HERE*/, CANVAS_HEIGHT / 2, 30, info, br);
												//καλώ μια συνάρτ της SGG, για να το τυπώσω. Μεγέθη : σε μονάδες κανβά. info: το κάνει 
												// construct και το περνάει σαν string μέσα.
	br.texture = "";				//το επαναφέρω πριν σχεδ τον κύκλο του ποντικιού.
	
	graphics::MouseState ms;
	graphics::getMouseState(ms);	//το mouse state θα το χρειαστούμε όχι μέσα στη draw κανονικά, αλλά για να ελέγξουμε την κατάσταση του ποντικιού, άρα μέσα στην update. 
	graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10.0f, br);
}

void Game::drawLevelScreen()
{
	//** Αφορούν την κατάσταση εν μέσω του παιχνιδιού, καθώς παίζω. **//

	graphics::Brush br;	

	//draw background.			// --> method for these.
	br.texture = std::string(ASSET_PATH) + "backgrounds\\mars1.png" /*"moon.png"*/;		//το texture φορτώνεται μια φορά και επαναχρησ/ται (το κάνει μέσα της η SGG).
	br.outline_opacity = 0.0f;															//to disappear the white line at the perimeter.
	graphics::drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_WIDTH * (500.0f/800.0f), br);	//png dimensions: 800*500 pixels (height=[578/768]*width ~= 0.75*width).

	/*XRONIKOS PERIORISMOS PAIXNIDIOY*/
	
	//GameObject::drawBrushFill(br, )		//--> make static.

	/////////////////////////////////////* Draw gameObjects -> καλύτερα με template ή με μια μέθοδο ??? ομοιόμορφα *///////////////////////////////

	/* Draw bunkers. */
	for (int i = 0; i < bunkers.size(); i++) {
		if (bunkers[i]) {
			bunkers[i]->set_draw_gobj_png(bunkerPNG);
			bunkers[i]->draw();		//** FIX: όλες τις draw().
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
		

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//kerdizei score -> (checkCollision(playerBullet, alien) , (checkCollision(playerBullet, meteorite) == true)
	//xanei score-> (checkCollision(player, meteorite)) == true)

	// UI/info Layer (με fonts). --> μπορεί kai se άλλη κλάση (π.χ. UI_class)!!!	//Στο τέλος!!! Θέλω να τυπώνεται πάνω απ όλα τ' άλλα.
	if (player)
	{
		//char info[40];
		//if (kills == 0) {
		//	score = 0;
		//}

		//alienKills = aliens.size();
		if (meteoKills == 0 && alienKills == 0) {
			score = 0;
		}

		//mpainei edw 
		//an skotose tous eksogiinous se ligo xrono     ' H
		//an patise gameover

		else if (player->getRemainingLife() != 0.0f) {
			score = (400 * alienKills) + (300 * meteoKills) + (150 * player->getRemainingLife());
		}
		else {
			//mpainei edw 
			//an ton skotosan oi aliens
			score = 400 * alienKills + 300 * meteoKills;  /*epenergoun thetika ta kills*/
		}
//EKTOS EAN DEN THELOUME NA VALOUME XRONO ? alla ine pio duskolo me xrono.
		//sprintf_s(info, "Time Remaining :%f", remainingTime/1000.0f); //upologismos sxore
		//sprintf_s(info, "Kills:%d", kills); //upologismos sxore

		//char info[40];																				//EKTOS EAN DEN THELOUME NA VALOUME XRONO ? alla ine pio duskolo me xrono.
		//sprintf_s(info, "NUMBER OF ALIENS:%d", remainingTime); //upologismos sxore
		//sprintf_s(info, "Kills:%d", alienKills); //upologismos sxore

		//graphics::drawText(600 /*FIX HERE*/, 40, 30, info, br);

		//if (debug_mode)
		//{
		//	char info[40];												//αντί για string βάζω buffer, για να γλιτ λίγο χώρο.
		//	sprintf_s(info, "Player pos: (%5.1f, %5.1f)", player->getPosX(), player->getPosY());
		//	graphics::drawText(50, 50, 15 /*40*/, info, br); 			//καλώ μια συνάρτ της SGG, για να το τυπώσω. Μεγέθη : σε μονάδες κανβά. //info: το κάνει construct και το περνάει σαν string μέσα.
		//}
	}

	float player_life = (player ? player->getRemainingLife() : 0.0f);

	br.outline_opacity = 0.0f;		//** FIX <-- method
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";

	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;	//(Γραμμική Παρεμβολή μεταξύ 2 τιμών) Όταν είναι γεμάτη η ζωή, θα ήθελα να είναι μπλε κι όταν ΔΕΝ είναι γεμάτη η ζωή, να είναι το 0.2f.
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.gradient = true;						//gradient ???
	br.gradient_dir_u = 1.0f;				//
	br.gradient_dir_v = 0.0f;				//αντιστρ τις τιμές των μεταβλ για να είναι το gradient οριζόντια.
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);
	br.outline_opacity = 0.5f;
	//??
	br.gradient = false;
	br.fill_opacity = 0.0f;			//καθόλου γέμισμα.
	graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 20, br);

	//** UI-info layer [end] //////

}

void Game::drawEndScreen()		//ΠΑΡΟΜΟΙΑ με την drawStartScreen (βελτ/ση ?? με template ??)
{
	/*Draw end screen background.*/				
	graphics::Brush br;
									//** FIX <-- method
	br.texture = std::string(ASSET_PATH) + "backgrounds\\gameover1.png";		//το texture φορτώνεται μια φορά και επαναχρησ/ται (το κάνει μέσα της η SGG).
	br.outline_opacity = 0.0f;												//to disappear the white line at the perimeter.
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 /*+offset*/, CANVAS_WIDTH, CANVAS_WIDTH * 0.473f, br);	//png dimensions: 1032*488 pixels (CANVAS_WIDTH/CANVAS_HEIGHT=1.5)

	char info[40];										//αντί για string βάζω buffer, για να γλιτ λίγο χώρο.
	sprintf_s(info, "GAME OVER");						//όλες οι μονάδες που χρησ/με -> σε μονάδες καμβά.
	graphics::drawText(370 , CANVAS_HEIGHT / 2, 60, info, br);

	br.fill_color[0] = 0.7f;				//** FIX <-- method
	br.fill_color[1] = 0.8f;
	br.fill_color[2] = 1.0f;
	sprintf_s(info, "Press 1 to try again");		
	graphics::drawText(50, 455, 20, info, br);

	br.fill_color[0] = 0.7f;				//** FIX <-- method
	br.fill_color[1] = 0.8f;
	br.fill_color[2] = 1.0f;
	sprintf_s(info, "Press ESC to exit");														
	graphics::drawText(50 , 475, 20, info, br);

	sprintf_s(info, "Total Score:%d", score);	 	//** FIX HERE: γίνεται αντικατ/ση στο info ??, βελτ/ση ?? **//
													//** ΔΕΝ ΔΟΥΛΕΥΕΙ ΤΟ ΕΞΙΤ ΘΑ ΠΡΕΠΕΙ ΝΑ ΤΟ ΑΛΛΑΞΟΥΜΕ
	graphics::drawText(800, 30 , 20, info, br);
}

void Game::drawPauseScreen()		//ΠΑΡΟΜΟΙΑ με την drawStartScreen (βελτ/ση ?? με template ??)
{
	/*Draw end screen background.*/
	graphics::Brush br;
									//** FIX <-- method
	br.texture = std::string(ASSET_PATH) + "backgrounds\\pause.png";		//το texture φορτώνεται μια φορά και επαναχρησ/ται (το κάνει μέσα της η SGG).
	br.outline_opacity = 0.0f;												//to disappear the white line at the perimeter.
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH * 0.473f, br);	//png dimensions: 1032*488 pixels (CANVAS_WIDTH/CANVAS_HEIGHT=1.5)
	// do something animated?
	char info[40];
	br.fill_color[0] = 0.0f;			//** FIX <-- method
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	sprintf_s(info, "PAUSED GAME");
	graphics::drawText(370, CANVAS_HEIGHT / 2 +20, 60, info, br);		
	br.fill_color[0] = 1.0f;			//** FIX <-- method
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	sprintf_s(info, "Press 1 to resume game");		
	graphics::drawText(50, 455, 20, info, br);
	sprintf_s(info, "Press 2 to exit");		
	graphics::drawText(50, 475, 20, info, br);
}


//////////////////////////////////////////////////////////** Window to canvas methods **/////////////////////////////////////////////////////////////////////

float Game::window2canvasX(float x)		//με όρισμα --> κάτι πρέπει να μετατρέπει
{
	//Πρέπει να κάνω scale τις μονάδες μου, άρα ό,τι μου έρθει σε window coordinates, θα ήθελα να επιστρ το x από μονάδες παραθύρου σε μονάδες καμβά.
	return x * CANVAS_WIDTH / (float)window_width /* το τρέχον window width */;
	/* FIX HERE for scaling at FULL screen. */
}

float Game::window2canvasY(float y)		//με όρισμα --> κάτι πρέπει να μετατρέπει
{
	return y * CANVAS_HEIGHT / (float)window_height /* το τρέχον window height */;
	//Να το πάρω από μέγιστο (???) window_height και να το μετατρέψω σε μονάδες καμβά.
/* FIX HERE for scaling at FULL screen. */
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
	musicInit();		//<--
}

void Game::musicInit(/*status_t status*/) {		//** CHECK

	if ((status == STATUS_PAUSE) || (status == STATUS_START)) {
		//0.5f: δε θέλω τη μέγιστη ένταση (background). fade time(??): σε msec
		graphics::playMusic(std::string(ASSET_PATH) + "music\\start-pause-music.mp3", 0.5f, true, 4000);
	}
	else if (status == STATUS_PLAYING) {
		graphics::playMusic(std::string(ASSET_PATH) + "music\\playing-music.mp3", 0.5f, true, 4000); //0.5f: δε θέλω τη μέγιστη ένταση (background). fade time(??): σε msec.
	}
	else if (status == STATUS_GAME_OVER) {
		graphics::playMusic(std::string(ASSET_PATH) + "music\\gameOver-music.mp3", 0.5f, true, 4000);		//0.5f: δε θέλω τη μέγιστη ένταση (background). fade time(??): σε msec.
	}
}



///////////////////////////////////////////////////** Constructor - Destructor **///////////////////////////////////////////////////

Game::Game()	//δεν καλεί την init() ???
{
}

Game::~Game()		//** CHECK !!!
{
	//{
//	if (player && player->getRemainingLife()==0.0f)		//An yparxei o player pointer 
//	{
//		delete player;		
//
//		status = STATUS_GAME_OVER;
//	}

	//for (int i = 0; i < 10; i++) {		// <--
	//	if (aliens[i]) {
	//		delete aliens[i];		//** CHECK
	//	}
	//}


	//list< vector<GameObject*> >::iterator list_it;

	/*if(!aliens.empty()){
		for (int i = 0; i <10; i++) {
			if (alienCol1[i]) {
				delete alienCol1[i];
			}else if (alienCol2[i]) {
				delete alienCol2[i];
			}else if (alienCol3[i]) {
				delete alienCol3[i];
			}
		}
		aliens.clear();
	}
	*/


	if (player)		//An yparxei o player pointer 
	{
		delete player;		//(θέλει και κάτι άλλο ??? για να σβήσει τελείως ???) --> CHECK tutorial
	}

	/*if (alien) {			//** CHECK
		delete alien;
	}*/

	if(playerBullet) {		/* Demo */		//** CHECK
		delete playerBullet;
	}

	if(alienBullet) {		//** CHECK
		delete alienBullet;
	}

	for (int i = 0; i < 3; i++) {		// <--
		if (bunkers[i]) {
			delete bunkers[i];		//** CHECK
		}
	}

	if (explosion) {              //** CHECK
		delete explosion;
	}

	if (meteorite) {               //** CHECK
		delete meteorite;
	}
}
