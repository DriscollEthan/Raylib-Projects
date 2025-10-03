#pragma once
#include "Vector2D.h"


class GlobalVariables
{
public:
	GlobalVariables() {}

	GlobalVariables(const GlobalVariables& _other) {}

	GlobalVariables operator=(const GlobalVariables& _other) { return *this; }

	//GLOABL VARIABLES:
	Driscoll::Vector2D ScreenSize = { 1920, 1024 };

	float ScreenX = ScreenSize.x;

	float ScreenY = ScreenSize.y;
};

