#include "Bunker.h"
#include "config.h"
#include "game.h"		

Bunker::Bunker(const Game& myGame, float bun_pos_x, float bun_pos_y, float bun_top_side_size)
	:GameObjCollRect(myGame, bun_pos_x, bun_pos_y, bun_top_side_size)
{
	size = 80.0f;
}

Bunker::~Bunker()
{
}


void Bunker::update()		
{
	GameObject::update();		
}

void Bunker::draw()			
{
	graphics::Brush br;					
	br.outline_opacity = 0.0f;			

	graphics::setScale(1.0f, 1.0f);			

	/*Draw bunker's shadow*/
	GameObject::drawSpriteTexture(br, 0.5f, draw_gobj_png.get_path_to_shadow());			
	graphics::drawRect(pos_x - 10.0f, pos_y + 5.0f, size * draw_gobj_png.get_png_dims_ratio(), size, br);		
	
	graphics::resetPose();		
	br.texture = "";		

	/*Draw bunker*/									
	float bun_life = Bunker::getRemainingLife();
	const char* bun_path_to_sprite = "";			

	if ( (0.7f < bun_life) && (bun_life <= 1.0f) )		
		bun_path_to_sprite = draw_gobj_png.get_path_to_sprite();			
	else if( (0.5f < bun_life) && (bun_life <= 0.7f) ) 						
		bun_path_to_sprite = "bunkers\\bunker_2x1_bottom_destroyed.png";
	else if( (0.3f < bun_life) && (bun_life <= 0.5f) )	
		bun_path_to_sprite = "bunkers\\bunker_1x2_top_destroyed.png";
	else if( (0.0f < bun_life) && (bun_life <= 0.3f) )		
		bun_path_to_sprite = "bunkers\\bunker_2x1_top_destroyed.png";
		

	GameObject::drawSpriteTexture(br, 1.0f, bun_path_to_sprite);		
	graphics::drawRect(pos_x, pos_y, size * draw_gobj_png.get_png_dims_ratio(), size, br);		//image dimensions: 66*140.

	graphics::resetPose();		
	br.texture = "";			



	if (game.getDebugMode())
	{
		graphics::Brush br;			

		br.outline_opacity = 1.0f;		
		br.texture = "";			
		GameObject::drawBrushFill(br, 0.2f, 0.7f, 0.4f, 0.3f, false);

		Rectangle bun_rect = getCollisionHull(draw_gobj_png.get_png_dims_ratio(), 1.0f);			
		graphics::drawRect(bun_rect.cx, bun_rect.cy, bun_rect.rec_width, bun_rect.rec_height, br);
	}
}

void Bunker::init()		
{
	width_factor = draw_gobj_png.get_png_dims_ratio();
	height_factor = 1.0f;
}
