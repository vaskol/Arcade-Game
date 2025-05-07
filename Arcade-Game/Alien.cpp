#include "alien.h"
#include "game.h"	
#include "enemy.h"		
#include "config.h"		


Alien::Alien(const Game& mygame, float al_pos_x, float al_pos_y)
	:Enemy(mygame)		
{
	init();			
	pos_x = al_pos_x;
	pos_y = al_pos_y;
}

Alien::~Alien()
{
}


void Alien::update()
{
	Enemy::update();	
}

void Alien::draw()
{
	graphics::Brush brush;

	graphics::setOrientation( draw_gobj_png.get_png_orientation() /*-90.0f*/);
	brush.outline_opacity = 0.0f;

	/*Draw alien's shadow.*/
	GameObject::drawSpriteTexture(brush, 0.5f, draw_gobj_png.get_path_to_shadow());			
	graphics::drawRect(pos_x - 10.0f, pos_y + 40.0f, size, size * draw_gobj_png.get_png_dims_ratio(), brush);

	/*Offset for movement.*/		// <--
	float offset = sinf(graphics::getGlobalTime() / 2000.0f) / 10;

	/*Draw alien.*/
	GameObject::drawSpriteTexture(brush, 1.0f, draw_gobj_png.get_path_to_sprite());			
	graphics::drawRect(pos_x, pos_y, size, size * draw_gobj_png.get_png_dims_ratio(), brush);

	graphics::resetPose();

	if (game.getDebugMode())
	{
		graphics::Brush br;					
		br.outline_opacity = 1.0f;
		br.texture = "";					

		GameObject::drawBrushFill(br, 0.6f, 0.2f, 0.2f, 0.3f, false);

		Disk met_disk = getCollisionHull(0.45f);			
		
		graphics::drawDisk(met_disk.cx, met_disk.cy, met_disk.radius, br);
	}
}

void Alien::init()				
{
	bool active = true;		

	pos_x = CANVAS_WIDTH - 50;
	pos_y = CANVAS_HEIGHT / 2 - 70;

	size = 50.0f;		
	speed = 0.25f;
}
