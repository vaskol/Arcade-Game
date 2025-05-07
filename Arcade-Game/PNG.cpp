#include "PNG.h"

/*
// PNG constructor for objects with rectangle collision hull.
PNG::PNG(float dims_ratio, float angle, const char* spritePath, const char* shadowPath, float width_ratio, float height_ratio)
	:png_dims_ratio(dims_ratio), png_orientation(angle), path_to_sprite(spritePath), path_to_shadow(shadowPath), png_obj_width_ratio(width_ratio), png_obj_height_ratio(height_ratio)
{
}

// PNG constructor for objects with disk collision hull.
PNG::PNG(float dims_ratio, float angle, const char* spritePath, const char* shadowPath, float radius_ratio)
	:png_dims_ratio(dims_ratio), png_orientation(angle), path_to_sprite(spritePath), path_to_shadow(shadowPath), png_obj_radius_ratio(radius_ratio)
{
}*/

// PNG constructor for objects without collision hull (non-collidable objects, e.g. explosion).
PNG::PNG(float dims_ratio, float angle, const char* spritePath, const char* shadowPath)
	: png_dims_ratio(dims_ratio), png_orientation(angle), path_to_sprite(spritePath), path_to_shadow(shadowPath)
{
}
