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
	const Driscoll::Vector2D GlobalScreenSize = Driscoll::Vector2D(1000.0f, 600.0f);

public:
	//GET GLOABL VARIABLES
	const Driscoll::Vector2D GetScreenSize();
};

