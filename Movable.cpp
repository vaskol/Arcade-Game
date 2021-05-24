#include "Movable.h"


float Movable::move() const
{
	if (move_to_east)
		return  speed * graphics::getDeltaTime();
	else
		return -(speed * graphics::getDeltaTime());
}
