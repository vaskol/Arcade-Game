#include "Meteorite.h"
#include "game.h"	



Meteorite::Meteorite(const Game& mygame)
	:Enemy(mygame)
{
	init();		/* CHECK -> tutorial */
}

Meteorite::~Meteorite()
{
}


void Meteorite::update()
{
	Enemy::update();

	rotation += 0.05f /*(μοίρες)*/ * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);

	if (pos_x < -size)
	{
		active = false;
	}
}

void Meteorite::draw()
{
	graphics::setOrientation(rotation);

	brush.outline_opacity = 0.0f;

	/*Draw meteorite's shadow.*/
	GameObject::drawSpriteTexture(brush, 0.5f, draw_gobj_png.get_path_to_shadow());			//** CHECK brush.
	graphics::drawRect(pos_x - 10.0f, pos_y + 40.0f, size, size * draw_gobj_png.get_png_dims_ratio(), brush);

	/*Draw meteorite.*/
	GameObject::drawSpriteTexture(brush, 1.0f, draw_gobj_png.get_path_to_sprite());			//** CHECK brush.
	graphics::drawRect(pos_x, pos_y, size, size * draw_gobj_png.get_png_dims_ratio(), brush);

	graphics::resetPose();

	if (game.getDebugMode())
	{
		graphics::Brush br;					//** CHECK (other brush).
		br.outline_opacity = 1.0f;
		br.texture = "";					//** CHECK.

		GameObject::drawBrushFill(br, 0.3f, 1.0f, 0.3f, 0.3f, false);

		Disk met_disk = getCollisionHull(0.45f);			//** CHECK inheritance return type --> διάλ.
		graphics::drawDisk(met_disk.cx, met_disk.cy, met_disk.radius, br);
	}
}

void Meteorite::init()		/* CHECK -> tutorial */
{
	size = 50 + 100 * rand0to1();			//Αρχική θέση μετεωρίτη.
	pos_x = CANVAS_WIDTH + 1.1f * size;
	pos_y = CANVAS_HEIGHT * rand0to1();

	speed = 15.0f;
	rotation = 360 * rand0to1();
}

/*
Shape* Meteorite::getCollisionHull() const {
	Disk met_disk = Disk(pos_x, pos_y, size * 0.42f);			//** FIX: να είναι διαφορετικό σε alien - meteorite (-> με παράμετρο ??)
	return &met_disk;
}*/
