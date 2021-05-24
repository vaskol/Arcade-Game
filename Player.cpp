#include "player.h"
#include "graphics.h"	//to graphics.h idi kanei include to arxeio "scancodes.h".
#include "game.h"		//<--  (στο GameObject ???)



//Kathisterei na ksekinisei, tou exo pei meta apo kapoio xrono na vazei ton paikti mesa.
//Σε Debug mode να μας δίνει τη θέση του διαστ/λοιου (συντ/νες).

Player::Player(const Game& mygame, float pl_pos_x, float pl_pos_y, float pl_size)
	:GameObjCollDisk(mygame, pl_pos_x, pl_pos_y, pl_size)		/*κατασκευαστής προγόνου*/
{
	size = 60.0f;
	speed = 15.0f;		//** FIX
}


void Player::update()	//allages sta state variables kathe antikeimenou.
{
	GameObject::update();

		//Kouniomaste me ta ASDW. (ston canva: pano aristeri gonia -> (0,0).)
		if (graphics::getKeyState(graphics::SCANCODE_A))	//Aristera.
		{
			pos_x -= move() / 50.0f /*10.0f*/;	//apostasi=taxitita*xronos (delta time: posos xronos mesolavise apo to proigoumeno update.)														
		}
		if (graphics::getKeyState(graphics::SCANCODE_D))	//Deksia.
		{
			pos_x += move() / 50.0f /*10.0f*/;
		}
		if (graphics::getKeyState(graphics::SCANCODE_W))	//Pano.
		{
			pos_y -= move() / 50.0f /*10.0f*/;
		}
		if (graphics::getKeyState(graphics::SCANCODE_S))	//Kato.
		{
			pos_y += move() / 50.0f /*10.0f*/;
		}
		
		//oriothetisi paikti
		if (pos_x < 0) pos_x = 0;							//Gia na mi bgainei ekso apo ta oria.
		if (pos_x > 250 - 60) pos_x = (250 - 60);
		if (pos_y < 0) pos_y = 0;
		if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;
}

void Player::draw()
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 70.0f);

	graphics::Brush br;					//** CHECK (local method variable).

	br.outline_opacity = 0.0f;					//na mi sxediazei to perigramma (isxuei kai gia ta 2: διαστημόπλοιο, glow, ...).

	graphics::setOrientation( draw_gobj_png.get_png_orientation() /*-90.0f*/);				//δίνω σε μοίρες πόσο θέλω να στρίψει (θετική φορά αντίθετα από αυτή των δεικτών του ρολογιού).
	//graphics::setScale(height, height);			//για τη μεγέθυνση-scale (ίδια τα height??). Αν το κάνω 1 φορά στην αρχή του παιχν. ισχύει για ΟΛΟ το παιχν.
	
	/*Draw spaceship's shadow.*/
	GameObject::drawSpriteTexture(br, 0.4f, draw_gobj_png.get_path_to_shadow());
	graphics::drawRect(pos_x - 10.0f, pos_y + size, size, size * draw_gobj_png.get_png_dims_ratio(), br);	//η σκιά πλησιάζει/απομακρ ανάλογα με το ύψος/scale.

	/**Draw spaceship.*/
	GameObject::drawSpriteTexture(br, 1.0f, draw_gobj_png.get_path_to_sprite());
	graphics::drawRect(pos_x, pos_y, size, size * draw_gobj_png.get_png_dims_ratio(), br);	//η σκιά πλησιάζει/απομακρ ανάλογα με το ύψος/scale.

	graphics::resetPose();										//επαναφέρει και τον προσανατ. και το scale.
	br.texture = "";	//το αναιρώ (κενό string). Afou xrisimopoiiso to texture gia na sxediaso to diastimoploio, prepei na to sviso, na min to exo sto brush mou.



	GameObject::drawBrushFill(br, 1.0f, 0.5f + glow * 0.5f, 0.0f, 1.0f, true);

	br.fill_secondary_opacity = 0.0f;		//antistoixa, stin alli mpanta (??) sto secondary, na einai 0.

	br.fill_secondary_color[0] = 0.3f;	//Thelo ki ena 2o xroma (pos fainetai??). Synolika na pigainei aplos pros to pio skoteino.
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;

	//graphics::setScale(height, height);
	graphics::drawDisk(pos_x - 40 /*(*height)*/, pos_y, 20, br);	//radius(??) =60 (μετά =20) (gia monades gyro sta 1000*500).
																	//(40*height): ό,τι βάλαμε για το offset της σκιάς, το βάζουμε και για το offset της φωτιάς.
	graphics::resetPose();

	//Θα μπορ η φωτιά να σχεδ πρώτη, για να είναι κάτω από το σκάφος.
	//Gia na ginei ayto me png eikones -> 2 eikones me diaforetiki foteinotita, allios(??) tis kanoume fade(??).
	//**************************************************************//

	if (game.getDebugMode())
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		GameObject::drawBrushFill(br, /*1.0f,*/ 1.0f, 0.3f, 0.3f, 0.3f, false);

		Disk pl_disk = getCollisionHull(0.533f);			//** CHECK inheritance return type --> διάλ.

		graphics::drawDisk(pl_disk.cx, pl_disk.cy, pl_disk.radius, br);
	}
}

void Player::init()		// <--
{
	
}


/*
void Player::checkStopByBunker(Bunker*& bun)
{
	float bun_PNG_dims_ratio = bun->get_draw_gobj_png().get_png_dims_ratio();

	float bun_x = bun->getPosX();
	float bun_y = bun->getPosY();
	float bun_half_w = bun->getCollisionHull(bun_PNG_dims_ratio, 1.0f).rec_width / 2.0f;
	float bun_half_h = bun->getCollisionHull(bun_PNG_dims_ratio, 1.0f).rec_height / 2.0f;
	float pl_radius = this->getCollisionHull(0.533f).radius;

	if ( pos_x >= (bun_x - bun_half_w) - pl_radius )
	{
		pos_x = (bun_x - bun_half_w) - pl_radius;
	}
	if ( pos_x <= (bun_x + bun_half_w) + pl_radius )
	{
		pos_x = (bun_x + bun_half_w) + pl_radius;
	}
	if ( pos_y <= (bun_y + bun_half_h) + pl_radius )
	{
		pos_y = (bun_y + bun_half_h) + pl_radius;
	}
	if ( pos_y >= (bun_y - bun_half_h) - pl_radius )
	{
		pos_y = (bun_y - bun_half_h) - pl_radius;
	}
}*/
