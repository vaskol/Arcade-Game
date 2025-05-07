#pragma once

class PNG
{
private:
	float png_dims_ratio = 1.0f;			// the ratio between png's width and height.
	float png_orientation = 0.0f;
	const char* path_to_sprite = ""; 
	const char* path_to_shadow = "";
	//float png_obj_width_ratio = 1.0f;		// The ratio between object's width and its png's width.
	//float png_obj_height_ratio = 1.0f;		// The ratio between object's height and its png's height.
	//float png_obj_radius_ratio = 1.0f;		// The ratio between the radius of object's (disk) collision hull and 
											// the smallest dimension (width or height) of its png. The purpose is to create the (disk) collision hull
											// with the minimum possible radius.

public:
	PNG() {}	// PNG default constructor.		

	// PNG constructor for objects with rectangle collision hull.
	//PNG(float dims_ratio, float angle, const char* spritePath, const char* shadowPath, float png_obj_width_ratio, float png_obj_height_ratio);
	// PNG constructor for objects with disk collision hull.
	//PNG(float dims_ratio, float angle, const char* spritePath, const char* shadowPath, float png_obj_radius_ratio);
	// PNG constructor for objects without collision hull (non-collidable objects, e.g. explosion).
	PNG(float dims_ratio, float angle, const char* spritePath, const char* shadowPath);
	
	/*
	void set_png_dims_ratio(float ratio) { png_dims_ratio = ratio; }
	void set_png_orientation(float degrees) { png_orientation = degrees; }
	void set_path_to_sprite(const char* spritePath) { path_to_sprite = spritePath; }
	void set_path_to_shadow(const char* shadowPath) { path_to_shadow = shadowPath; }
	*/

	float get_png_dims_ratio() const { return png_dims_ratio; }
	float get_png_orientation() const { return png_orientation; }
	const char* get_path_to_sprite() const { return path_to_sprite; }
	const char* get_path_to_shadow() const { return path_to_shadow; }
	//float get_png_obj_width_ratio() const { return png_obj_width_ratio; }
	//float get_png_obj_height_ratio() const { return png_obj_height_ratio; }
	//float get_png_obj_radius_ratio() const { return png_obj_radius_ratio; }
};
