#pragma once

#include "util.h"
#include "graphics.h"	
#include "PNG.h"




class GameObject	
{
protected:
	const class Game& game;		
	float pos_x, pos_y;
	float size;  //= 0.0f;		
	float life = 1.0f;		
	bool active = true;		
	


	PNG draw_gobj_png;		// the png needed for each drawable game object.

public:
	GameObject(const class Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size);
	virtual ~GameObject() {}		//virtual destructor, so objects of subclasses can be deleted correctly/successfully.

	//** FIX
	virtual void update();
	virtual void draw()=0;
	virtual void init()=0;

	float getPosX() const { return pos_x; }	//inline (ìéêñÞ)
	float getPosY() const { return pos_y; }	//inline (ìéêñÞ)

	float getSize() const { return size; }	//inline (ìéêñÞ)

	bool isActive() const { return active; }		

	void drainLife(float amount);		
	float getRemainingLife() const { return life; }

	PNG get_draw_gobj_png() const { return draw_gobj_png; }		
	void set_draw_gobj_png(PNG& gobjPNG) { draw_gobj_png = gobjPNG; }		

	void drawSpriteTexture(graphics::Brush& br, float fill_op, const char* path_to_sprite);
	void drawBrushFill(graphics::Brush& br, float fill_0, float fill_1, float fill_2, float fill_op, bool grad);
};
