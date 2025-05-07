#include <random>
#include "config.h"
#include "game.h"			
#include "player.h"
#include "bullet.h"


Bullet::Bullet(const Game& mygame, float bul_pos_x, float bul_pos_y /*, float bul_size*/)
	:GameObjCollRect(mygame, bul_pos_x, bul_pos_y, size)		
{
	init();			
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	GameObject::update();

	if (pos_x >= CANVAS_WIDTH + size / 2)
	{
		active = false;
	}

	if (active)			
	{
		pos_x += move() / 10.0f;		
	}
}

void Bullet::draw()		
{

	br.outline_opacity = 0.0f;			

	graphics::setOrientation(draw_gobj_png.get_png_orientation() /*90.0f*/);		
			
	/*Draw bullet shadow.*/
	GameObject::drawSpriteTexture(br, 0.4f, draw_gobj_png.get_path_to_shadow());
	graphics::drawRect(pos_x - 10.0f, pos_y + 40.0f, size * draw_gobj_png.get_png_dims_ratio(), size, br);

	/*Draw bullet.*/
	GameObject::drawSpriteTexture(br, 1.0f, draw_gobj_png.get_path_to_sprite());
	graphics::drawRect(pos_x, pos_y, size * draw_gobj_png.get_png_dims_ratio(), size, br);

	graphics::resetPose();		

	if (game.getDebugMode())
	{
		graphics::Brush br;		

		br.outline_opacity = 1.0f;	
		br.texture = "";		
		GameObject::drawBrushFill(br, 0.2f, 0.4f, 0.7f, 0.3f, false);

		Rectangle bul_rect = getCollisionHull(draw_gobj_png.get_png_dims_ratio(), 1.0f);
		graphics::drawRect(bul_rect.cx, bul_rect.cy, bul_rect.rec_width, bul_rect.rec_height*0.4f, br);		
	}
}

void Bullet::init()			
{
	speed = 6.0f;	
	size = 30.0f;

	width_factor = draw_gobj_png.get_png_dims_ratio();
	height_factor = 1.0f;
}
