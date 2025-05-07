#include "explosion.h"
#include "game.h"	


Explosion::Explosion(const Game& mygame, float bul_pos_x, float bul_pos_y)
	:GameObject(mygame, bul_pos_x, bul_pos_y, size)		// size = 30.0f; (το μέγεθος με το οποίο αρχικ/κε η σφαίρα στην init() )
{
	init();			//** CHECK (tutorial).
}

Explosion::~Explosion()
{
}


void Explosion::update()
{
	GameObject::update();

	/*
	while (active) {
		if (expl_sinf >= 1.0f) {
			active = false; //kati allo
		}
		break;
	}*/
}

void Explosion::draw()
{
	graphics::setOrientation(rotation);		// <--
	brush.outline_opacity = 0.0f;		// <--

	for(int i=0; i<10; i++){
		/*Draw explosion.*/
		float expl_sinf = sinf(graphics::getGlobalTime() / 2000.0f) / 10.0f;;
		
		GameObject::drawSpriteTexture(brush, 0.5f, draw_gobj_png.get_path_to_sprite());			//** CHECK brush.
		graphics::drawRect(pos_x, pos_y, size * i * expl_sinf, size * i * expl_sinf, brush);

		graphics::resetPose();
	}
}

void Explosion::init()		/* CHECK -> tutorial */
{
	size = 50 + 100 * rand0to1();			//Αρχική θέση μετεωρίτη.
	speed = 0.3f;

	//brush.outline_opacity = 0;		
}
