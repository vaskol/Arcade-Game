#include "player.h"
#include "graphics.h"	
#include "game.h"		

//Waits few seconds in order to start the game
Player::Player(const Game& mygame, float pl_pos_x, float pl_pos_y, float pl_size)
	:GameObjCollDisk(mygame, pl_pos_x, pl_pos_y, pl_size)		
{
	size = 60.0f;
	speed = 15.0f;		
}

void Player::update()	
{
	GameObject::update();
	
		//Controls with ASDW
		if (graphics::getKeyState(graphics::SCANCODE_A))	//Aristera.
		{
			pos_x -= move() / 50.0f /*10.0f*/;														
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
		
		if (pos_x < 0) pos_x = 0;							
		if (pos_x > 250 - 60) pos_x = (250 - 60);
		if (pos_y < 0) pos_y = 0;
		if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;
}

void Player::draw()
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 70.0f);

	graphics::Brush br;					

	br.outline_opacity = 0.0f;					

	graphics::setOrientation( draw_gobj_png.get_png_orientation());				
	GameObject::drawSpriteTexture(br, 0.4f, draw_gobj_png.get_path_to_shadow());
	graphics::drawRect(pos_x - 10.0f, pos_y + size, size, size * draw_gobj_png.get_png_dims_ratio(), br);	
	GameObject::drawSpriteTexture(br, 1.0f, draw_gobj_png.get_path_to_sprite());
	graphics::drawRect(pos_x, pos_y, size, size * draw_gobj_png.get_png_dims_ratio(), br);	
	graphics::resetPose();	
	
	br.texture = "";	
	GameObject::drawBrushFill(br, 1.0f, 0.5f + glow * 0.5f, 0.0f, 1.0f, true);
	
	br.fill_secondary_opacity = 0.0f;		
	br.fill_secondary_color[0] = 0.3f;	
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;
	
	graphics::drawDisk(pos_x - 40 /*(*height)*/, pos_y, 20, br);																
	graphics::resetPose();

	if (game.getDebugMode())
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		GameObject::drawBrushFill(br, /*1.0f,*/ 1.0f, 0.3f, 0.3f, 0.3f, false);
		Disk pl_disk = getCollisionHull(0.533f);			
		graphics::drawDisk(pl_disk.cx, pl_disk.cy, pl_disk.radius, br);
	}
}
void Player::init(){}

