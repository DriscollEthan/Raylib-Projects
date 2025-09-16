#include "Collectable.h"

Collectable::Collectable() : Object()
{
	bIsAlive = true;
}

Collectable::Collectable(raylib::Image _image, raylib::Vector2 _position)
{
	Image = _image;
	Position = _position;

	HitboxRadius = Image.width;
	bIsAlive = true;
}

Collectable::Collectable(Collectable& const _other)
{
	Image = _other.Image;
	HitboxRadius = _other.HitboxRadius;
	bIsAlive = _other.bIsAlive;
}

Collectable Collectable::operator=(Collectable& const _other)
{
	Image = _other.Image;
	HitboxRadius = _other.HitboxRadius;
	bIsAlive = _other.bIsAlive;
	return *this;
}

Collectable::~Collectable()
{
}
