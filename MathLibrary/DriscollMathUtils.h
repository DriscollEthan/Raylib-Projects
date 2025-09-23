#pragma once

//Includes all of the Headers from Ethan Driscoll's custom Math Library.

#include "Utils.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3.h"
#include "Color.h"

namespace Driscoll
{
//Macro Color Calls:
#define RED Driscoll::Color::Red();
#define GREEN Driscoll::Color::Green();
#define BLUE Driscoll::Color::Blue();
#define WHITE Driscoll::Color::White();
#define BLACK Driscoll::Color::Black();
#define CLEAR Driscoll::Color::CLear();
#define ORANGE Driscoll::Color::Orange();
#define PINK Driscoll::Color::Pink();
#define YELLOW Driscoll::Color::Yellow();
}