#pragma once
#include "Object.h"
class Collectable : public Object
{
public:
	//Constructors and Destructors
	Collectable();

	Collectable(raylib::Image _image, raylib::Vector2 _position);

	Collectable(Collectable& const _other);

	Collectable operator=(Collectable& const _other);

	~Collectable();
};

