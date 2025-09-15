#include "Object.h"

Object::Object()
{
	Position = raylib::Vector2(0, 0);
	Image = raylib::Image();
	Hitbox = raylib::Rectangle(raylib::Vector2(0, 0), Image.GetSize());
}

Object::Object(Object& const _other)
{
	Image = _other.Image;
	Hitbox = _other.Hitbox;
}

Object Object::operator=(Object& const _other)
{
	Image = _other.Image;
	Hitbox = _other.Hitbox;
	return *this;
}

Object::~Object()
{

}

void Object::OverrideHitBoxSize(raylib::Vector2 _size)
{
	Hitbox.SetSize(_size);
	Hitbox.SetPosition(Position);
}
