#pragma once

#include "../raylib-cpp/include/raylib-cpp.hpp"
#include "Vector2D.h"


class Object
{
public:
	Object();

	Object(Object& const _other);

	Object operator=(Object& const _other);

	~Object();

	void OverrideHitBoxSize(raylib::Vector2 _size);

public:	

	Driscoll::Vector2D Position;

	Texture2D Image;

	raylib::Rectangle Hitbox;
};