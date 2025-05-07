#pragma once

#include "util.h"
#include "graphics.h"		//** (for brush) CHECK.
#include "PNG.h"
//#include "Collidables.h"
//#include "config.h"		//<--



class GameObject //: public Drawable		//na akolouthei to idio public interface me to "Game" ???. gia logous symvatotitas, kliseon kai omoiomorfias.
{
protected:
	const class Game& game;		// !!! (��� "���������" ��� ��� ����� Game, ����� �� ���� include)
	float pos_x, pos_y;
	float size;  //= 0.0f;		// <--
	float life = 1.0f;		//�������� ����, ������ ��� ����� ������ �� gameObject.
	bool active = true;		//** CHECK tutorial.
	
	//graphics::Brush brush;

	PNG draw_gobj_png;		// the png needed for each drawable game object.

public:
	GameObject(const class Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size);
	virtual ~GameObject() {}		//virtual destructor, so objects of subclasses can be deleted correctly/successfully.

	//** FIX
	virtual void update();
	virtual void draw()=0;
	virtual void init()=0;

	float getPosX() const { return pos_x; }	//inline (�����)
	float getPosY() const { return pos_y; }	//inline (�����)

	float getSize() const { return size; }	//inline (�����)

	bool isActive() const { return active; }		//** CHECK (const ����� ???)

	void drainLife(float amount);		//���� �� ����� ����������� ���� ��� ��� Player (�� ���� gameObjects ����� ���� active/inactive)
	float getRemainingLife() const { return life; }

	PNG get_draw_gobj_png() const { return draw_gobj_png; }		// <-- ��� ������ �������.
	void set_draw_gobj_png(PNG& gobjPNG) { draw_gobj_png = gobjPNG; }		//** CHECK ref.

	void drawSpriteTexture(graphics::Brush& br, float fill_op, const char* path_to_sprite);
	void drawBrushFill(graphics::Brush& br, float fill_0, float fill_1, float fill_2, float fill_op, bool grad);
};
