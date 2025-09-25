#pragma once
#include "Object.h"
#include "Vector2D.h"


class GlobalVariableObject : public Object
{
public:
	GlobalVariableObject() {}

	GlobalVariableObject(const GlobalVariableObject& _other) {}

	GlobalVariableObject operator=(const GlobalVariableObject& _other) { return *this; }
protected:
	//GLOABL VARIABLES:
	const Driscoll::Vector2D GlobalScreenSize = Driscoll::Vector2D(1500.0f, 900.0f);

	int GlobalX = GlobalScreenSize.x;
	int GlobalY = GlobalScreenSize.y;

public:
	//GET GLOABL VARIABLES
	const Driscoll::Vector2D GetScreenSize() { return GlobalScreenSize; }

	int GetScreenSizeIntX() { return GlobalX; }
	int GetScreenSizeIntY() { return GlobalY; }
};

