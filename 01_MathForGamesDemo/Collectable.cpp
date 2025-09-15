#include "Collectable.h"

Collectable::Collectable() : Object()
{

}

Collectable::Collectable(raylib::Image _image, raylib::Vector2 _position)
{
	Image = _image;
	Position = _position;

	Hitbox = raylib::Rectangle(raylib::Vector2(0, 0), Image.GetSize());
}

Collectable::Collectable(Collectable& const _other)
{
	Image = _other.Image;
	Hitbox = _other.Hitbox;
}

Collectable Collectable::operator=(Collectable& const _other)
{
	Image = _other.Image;
	Hitbox = _other.Hitbox;
	return *this;
}

Collectable::~Collectable()
{
}
