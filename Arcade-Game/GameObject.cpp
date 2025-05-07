#include "gameobject.h"
#include "game.h"

GameObject::GameObject(const Game& mygame, float gobj_pos_x, float gobj_pos_y, float gobj_size)	
	:game(mygame), pos_x(gobj_pos_x), pos_y(gobj_pos_y), size(gobj_size)
{
}

void GameObject::update()
{
	active = life;
}

void GameObject::drainLife(float amount)
{
	life = std::max<float>(0.0f, life - amount);
}

void GameObject::drawSpriteTexture(graphics::Brush& br, float fill_op, const char* path_to_sprite)
{
	br.fill_opacity = fill_op;
	br.texture = std::string(ASSET_PATH) + path_to_sprite;
}

void GameObject::drawBrushFill(graphics::Brush& br, float fill_0, float fill_1, float fill_2, float fill_op, bool grad)
{
	br.fill_color[0] = fill_0;
	br.fill_color[1] = fill_1;
	br.fill_color[2] = fill_2;
	br.fill_opacity = fill_op;
	br.gradient = grad;
}
