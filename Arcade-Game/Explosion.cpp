#include "explosion.h"
#include "game.h"	


Explosion::Explosion(const Game& mygame, float bul_pos_x, float bul_pos_y)
	:GameObject(mygame, bul_pos_x, bul_pos_y, size)		
{
	init();		
}

Explosion::~Explosion()
{
}


void Explosion::update()
{
	GameObject::update();
}

void Explosion::draw()
{
	graphics::setOrientation(rotation);		
	brush.outline_opacity = 0.0f;		

	for(int i=0; i<10; i++){
		/*Draw explosion.*/
		float expl_sinf = sinf(graphics::getGlobalTime() / 2000.0f) / 10.0f;;
		
		GameObject::drawSpriteTexture(brush, 0.5f, draw_gobj_png.get_path_to_sprite());			
		graphics::drawRect(pos_x, pos_y, size * i * expl_sinf, size * i * expl_sinf, brush);

		graphics::resetPose();
	}
}

void Explosion::init()		
{
	size = 50 + 100 * rand0to1();			
	speed = 0.3f;	
}
