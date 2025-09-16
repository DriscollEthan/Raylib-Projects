#include "Object.h"

Object::Object()
{
	Position = raylib::Vector2(0, 0);
	Image = raylib::Image();
	HitboxRadius = 0.0f;
}

Object::Object(Object& const _other)
{
	Image = _other.Image;
	HitboxRadius = _other.HitboxRadius;
}

Object Object::operator=(Object& const _other)
{
	Image = _other.Image;
	HitboxRadius = _other.HitboxRadius;
	return *this;
}

Object::~Object()
{

}

void Object::OverrideHitBoxSize(float _radius)
{
	HitboxRadius = _radius;
}
