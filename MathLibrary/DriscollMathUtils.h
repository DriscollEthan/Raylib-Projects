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
#define RED Color::Red();
#define GREEN Color::Green();
#define BLUE Color::Blue();
#define WHITE Color::White();
#define BLACK Color::Black();
#define CLEAR Color::Clear();
#define ORANGE Color::Orange();
#define PINK Color::Pink();
#define YELLOW Color::Yellow();


  //STRUCT OF LOCAL DATA
  struct LocalData2D
  {
    Vector2D LocalPosition;
    float LocalRotation;
    Vector2D LocalScale;

    LocalData2D()
    {
      LocalPosition = { 0, 0 };
      LocalRotation = 0;
      LocalScale = { 1, 1 };
    }

    LocalData2D(Vector2D _position, float _rotation, Vector2D _scale)
    {
      LocalPosition = _position;
      LocalRotation = _rotation;
      LocalScale = _scale;
    }

    LocalData2D(const LocalData2D& _other)
    {
      LocalPosition = _other.LocalPosition;
      LocalRotation = _other.LocalRotation;
      LocalScale = _other.LocalScale;
    }

    LocalData2D operator =(const LocalData2D& _other)
    {
      LocalPosition = _other.LocalPosition;
      LocalRotation = _other.LocalRotation;
      LocalScale = _other.LocalScale;
      return *this;
    }
  };
}