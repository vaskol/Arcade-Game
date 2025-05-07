#include "Bunker.h"
#include "config.h"
#include "game.h"		//<--  (��� GameObject ???)


Bunker::Bunker(const Game& myGame, float bun_pos_x, float bun_pos_y, float bun_top_side_size  /* <-- FIX !! */)
	:GameObjCollRect(myGame, bun_pos_x, bun_pos_y, bun_top_side_size /* <-- FIX !! */)
{
	//init();		//** CHECK
	size = 80.0f;
}

Bunker::~Bunker()
{
}


void Bunker::update()		//�� ������� � ��������� ��� ������� �� �� ����� (�� ������� ����). �� ������ enum "state" ����.
{
	GameObject::update();		//** FIX
}

void Bunker::draw()			//++ �� ����.
{
	graphics::Brush br;					//** CHECK (local method variable).
	br.outline_opacity = 0.0f;			//na mi sxediazei to perigramma (isxuei gia ��� �� ������� �� �� Bunker).

	graphics::setScale(1.0f, 1.0f);			//��� �� ���������-scale (���� �� height??). �� �� ���� 1 ���� ���� ���� ��� �����. ������ ��� ��� �� �����.

	/*Draw bunker's shadow*/
	GameObject::drawSpriteTexture(br, 0.5f, draw_gobj_png.get_path_to_shadow());			//** CHECK brush.
	graphics::drawRect(pos_x - 10.0f, pos_y + 5.0f, size * draw_gobj_png.get_png_dims_ratio(), size, br);		//image dimensions: 66*140.

	
	graphics::resetPose();		//���������� ��� ��� ��������. ��� �� scale.
	br.texture = "";			//�� ������ (���� string). 

	/*Draw bunker*/									//** FIX: �� ��������� ������� -> �� ��� ������ (CHECK ��� ���� ����� draw).
	float bun_life = Bunker::getRemainingLife();
	const char* bun_path_to_sprite = "";			// initialize char array.

	if ( (0.7f < bun_life) && (bun_life <= 1.0f) )		//**CHECK: �� status??
		bun_path_to_sprite = draw_gobj_png.get_path_to_sprite();			//** FIX.
	else if( (0.5f < bun_life) && (bun_life <= 0.7f) ) 						
		bun_path_to_sprite = "bunkers\\bunker_2x1_bottom_destroyed.png";
	else if( (0.3f < bun_life) && (bun_life <= 0.5f) )	
		bun_path_to_sprite = "bunkers\\bunker_1x2_top_destroyed.png";
	else if( (0.0f < bun_life) && (bun_life <= 0.3f) )		
		bun_path_to_sprite = "bunkers\\bunker_2x1_top_destroyed.png";
	//else if(bun_life <= 0.0f)		//** FIX: ���� ����� 0 � ��� -> ��� �� ���� ������.		
		//bun_path_to_object = "";

	GameObject::drawSpriteTexture(br, 1.0f, bun_path_to_sprite);			//** CHECK brush.
	graphics::drawRect(pos_x, pos_y, size * draw_gobj_png.get_png_dims_ratio(), size, br);		//image dimensions: 66*140.

	graphics::resetPose();		//���������� ��� ��� ��������. ��� �� scale.
	br.texture = "";			//�� ������ (���� string). 



	if (game.getDebugMode())
	{
		graphics::Brush br;				//** CHECK

		br.outline_opacity = 1.0f;		//** (same brush) CHECK.
		br.texture = "";				//** CHECK
		GameObject::drawBrushFill(br, 0.2f, 0.7f, 0.4f, 0.3f, false);

		Rectangle bun_rect = getCollisionHull(draw_gobj_png.get_png_dims_ratio(), 1.0f);			//** CHECK inheritance return type --> ����.	
		graphics::drawRect(bun_rect.cx, bun_rect.cy, bun_rect.rec_width, bun_rect.rec_height, br);
	}
}

void Bunker::init()		//** CHECK
{
	//size = 70.0f;	
	//one_collision_dead = false;
	width_factor = draw_gobj_png.get_png_dims_ratio();
	height_factor = 1.0f;
}
