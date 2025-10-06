#pragma once

//Includes all of the Headers from Ethan Driscoll's custom Math Library.

#include "Utils.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Color.h"

namespace Driscoll
{
//Macro Color Calls:
#define RED Color::Red()
#define DARKRED Color::DarkRed()

#define GREEN Color::Green()

#define BLUE Color::Blue()
#define CYAN Color::Cyan()
#define TEAL Color::Teal()

#define WHITE Color::White()
#define BLACK Color::Black()
#define DARKGREY Color::DarkGrey()
#define GREY Color::Grey()
#define CLEAR Color::Clear()

#define ORANGE Color::Orange()

#define PINK Color::Pink()

#define YELLOW Color::Yellow()
}