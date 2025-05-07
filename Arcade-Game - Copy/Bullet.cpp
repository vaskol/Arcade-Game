#include <random>

//#include "graphics.h"
#include "config.h"
#include "game.h"			//<--  (��� GameObject ???)
#include "player.h"
#include "bullet.h"


Bullet::Bullet(const Game& mygame, float bul_pos_x, float bul_pos_y /*, float bul_size*/)
	:GameObjCollRect(mygame, bul_pos_x, bul_pos_y, size)		// size = 30.0f; (�� ������� �� �� ����� �����/�� � ������ ���� init() )
{
	init();			//** CHECK (tutorial).
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

	if (active)			// LOGIKA PREPEI NA KINEITAI MEXRI NA VREI COLLISIONS
	{
		pos_x += move() / 10.0f;		//** FIX
	}
}

void Bullet::draw()		//** FIX: �� ��� ��������� ��� ��� ������ �������.  ++ ���'� ��� ������� (+���??)
{
	//** CHECK �� brush.
	br.outline_opacity = 0.0f;			//na mi sxediazei to perigramma (isxuei gia ��� �� ������� �� �� Bunker).

	graphics::setOrientation(draw_gobj_png.get_png_orientation() /*90.0f*/);		//���� �� ������ ���� ���� �� ������� (������ ���� �������� ��� ���� ��� ������� ��� ��������).
	//graphics::setScale(1.0f, 1.0f);			//��� �� ���������-scale (���� �� height??). �� �� ���� 1 ���� ���� ���� ��� �����. ������ ��� ��� �� �����.

	/*Draw bullet shadow.*/
	GameObject::drawSpriteTexture(br, 0.4f, draw_gobj_png.get_path_to_shadow());
	graphics::drawRect(pos_x - 10.0f, pos_y + 40.0f, size * draw_gobj_png.get_png_dims_ratio(), size, br);

	/*Draw bullet.*/
	GameObject::drawSpriteTexture(br, 1.0f, draw_gobj_png.get_path_to_sprite());
	graphics::drawRect(pos_x, pos_y, size * draw_gobj_png.get_png_dims_ratio(), size, br);


	// ++ texture ??
	graphics::resetPose();		

	if (game.getDebugMode())
	{
		graphics::Brush br;			//** CHECK (-> ����� )

		br.outline_opacity = 1.0f;	//** (same brush) CHECK.
		br.texture = "";			//** CHECK
		GameObject::drawBrushFill(br, 0.2f, 0.4f, 0.7f, 0.3f, false);

		Rectangle bul_rect = getCollisionHull(draw_gobj_png.get_png_dims_ratio(), 1.0f);
		graphics::drawRect(bul_rect.cx, bul_rect.cy, bul_rect.rec_width, bul_rect.rec_height*0.4f, br);		//*0.4f -> ��� ��� player bullet (alien ???)
	}
}

void Bullet::init()			//**FIX: ���� ��� init() + constructors.
{
	speed = 6.0f;	//0.2f;
	size = 30.0f;

	width_factor = draw_gobj_png.get_png_dims_ratio();
	height_factor = 1.0f;
}


/*
Shape* Bullet::getCollisionHull() const		//** CHECK inheritance return type --> ����.
{
	Rectangle* bul_rect = new Rectangle(pos_x, pos_y, size * draw_gobj_png.get_png_dims_ratio(), size);			//** CHECK
	return bul_rect;
}*/
