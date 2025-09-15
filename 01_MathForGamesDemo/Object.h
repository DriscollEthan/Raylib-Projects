#pragma once

#include "../raylib-cpp/include/raylib-cpp.hpp"


class Object
{
public:
	Object();

	Object(Object& const _other);

	Object operator=(Object& const _other);

	~Object();

	void OverrideHitBoxSize(raylib::Vector2 _size);

public:	

	raylib::Vector2 Position;

	raylib::Image Image;

	raylib::Rectangle Hitbox;
};