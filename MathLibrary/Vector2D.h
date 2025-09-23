#pragma once
#include <iostream>
#include <string>

#include "Utils.h"

namespace Driscoll 
{
	struct Vector2D
	{
		union
		{
			struct { float x, y; };
			float data[2];
		};


		/// <summary>
		/// Default Constructor - Initizalize all Components to Zero.
		/// <summary>
		Vector2D() { x = 0; y = 0; }

		/// <summary>
		/// Default Constructor - Initizalize all Components to Zero.
		/// <summary>
		Vector2D(float _x, float _y) { x = _x; y = _y; }

		//REQUIRES RAYLIBCPP LIB TO BE INCLUDED BEFORE THIS HEADER
#ifdef RAYLIB_CPP_INCLUDE_RAYLIB_CPP_HPP_
		// implicit conversion from raylib-cpp Vec2 to our Vec2
		Vector2D(const raylib::Vector2& _rVector2)
		{
			x = _rVector2.x;
			y = _rVector2.y;
		}

		// implicit conversion from our Vec2 to raylib-cpp Vec2
		operator raylib::Vector2() const
		{
			return { x, y };
		}
#endif

#ifdef RAYLIB_H
		// implicit conversion from raylib Vec2 to our Vec2
		Vector2D(const ::Vector2& _rVector2)
		{
			x = _rVector2.x;
			y = _rVector2.y;
		}

		// implicit conversion from our Vec2 to raylib Vec2
		operator ::Vector2() const
		{
			return { x, y };
		}
#endif

		//Sets the Vector back to (0,0)
		void Zero()
		{
			x = 0;
			y = 0;
		}

		//Returns the Length of the Vector2D
		float Magnitude() const
		{
			return sqrtf((x * x) + (y * y));
		}

		//Returns the Length Squared of the Vector2D
		float MagnitudeSqr() const
		{
			return ((x * x) + (y * y));
		}

		//Returns the Unit Vector2D
		void Normalise()
		{
			float mag = this->Magnitude();

			x /= mag;
			y /= mag;

			return;
		}

		//Safely Returns the Unit Vector2D
		void SafeNormalise()
		{
			if (this->Magnitude() != 0)
			{
				Normalise();
			}
			return;
		}

		//Returns a Vector2D that is a unit Vector2D
		Vector2D Normalised()
		{
			Vector2D copy = *this;
			copy.Normalise();

			return copy;
		}

		//Returns a Vector2D that is a unit Vector2D
		Vector2D SafeNormalised()
		{
			if (this->Magnitude() != 0)
			{
				Vector2D copy = *this;
				copy.SafeNormalise();

				return copy;
			}
			return Vector2D();
		}

		//Returns the Dot Product of a Vector2D
		float Dot(const Vector2D& _otherVector) const
		{
			return ((x * _otherVector.x) + (y * _otherVector.y));
		}

		//Returns the Dot Product of two Vector2Ds
		static float Dot(Vector2D& const _firstVector, Vector2D& const _secondVector)
		{
			return _firstVector.Dot(_secondVector);
		}

		//Returns the Perpendicular Vector setup as a Right Handed System!
		Vector2D Perpendicular() const
		{
			return { -y, x };
		}

		//Sets and Returns the Absolute values for the Vector2D
		Vector2D Absolute()
		{
			if (x < 0)
			{
				x *= -1;
			}
			if (y < 0)
			{
				y *= -1;
			}

			return *this;
		}

		bool Equals(const Vector2D& _otherVector) const
		{
			return ((x == _otherVector.x) && (y == _otherVector.y));
		}

		bool NearlyEquals(const Vector2D& _otherVector, float _tolerance = MAX_FLOAT_DELTA) const
		{
			Vector2D distance = { x - _otherVector.x, y - _otherVector.y };
			distance.Absolute();

			return ((distance.x < _tolerance) && (distance.y < _tolerance));
		}

		float Distance(const Vector2D& _otherVector) const
		{
			return (*this - _otherVector).Magnitude();
		}

		float DistanceSqr(const Vector2D& _otherVector) const
		{
			return (*this - _otherVector).MagnitudeSqr();
		}

		static float Distance(const Vector2D& _firstVector, const Vector2D& _secondVector)
		{
			return _firstVector.Distance(_secondVector);
		}

		static float DistacneSqr(const Vector2D& _firstVector, const Vector2D& _secondVector)
		{
			return _firstVector.DistanceSqr(_secondVector);
		}

		//Find Angle Between 2 Vectors2D
		float AngleBetween(const Vector2D& _otherVector)
		{
			return std::atan2f(y - _otherVector.y, x - _otherVector.x);
		}
		//Operators

		// returns true if every component is equal to the other in the other vector
		bool operator == (const Vector2D& _otherVector) const
		{
			return Equals(_otherVector);
		}

		// returns a new Vector containing the summed value of each component
		Vector2D operator +(const Vector2D& _otherVector) const
		{
			Vector2D tempVector = { x, y };
			tempVector.x += _otherVector.x;
			tempVector.y += _otherVector.y;
			return tempVector;
		}

		// assigns this Vector the value of this vector added to the other vector
		Vector2D& operator +=(const Vector2D& _otherVector)
		{
			x += _otherVector.x;
			y += _otherVector.y;
			return *this;
		}

		// returns a new Vector containing the subtracted value of each component
		Vector2D operator -(const Vector2D& _otherVector) const
		{
			Vector2D tempVector = { x, y };
			tempVector.x -= _otherVector.x;
			tempVector.y -= _otherVector.y;
			return tempVector;
		}

		// assigns this Vector the value of this vector subtracted from the other vector
		Vector2D& operator -=(const Vector2D& _otherVector)
		{
			x -= _otherVector.x;
			y -= _otherVector.y;
			return *this;
		}

		// returns a new Vector where each component is scaled by the scalar value
		Vector2D operator*(float _otherFloat) const
		{
			Vector2D tempVector = { x, y };
			tempVector.x *= _otherFloat;
			tempVector.y *= _otherFloat;
			return tempVector;
		}
		// returns a new Vector where each component is scaled by the Vector Component Aligned with it.
		Vector2D operator*(Vector2D _otherVector) const
		{
			Vector2D tempVector = { x, y };
			tempVector.x *= _otherVector.x;
			tempVector.y *= _otherVector.y;
			return tempVector;
		}

		// assigns this Vector the value of this vector where each component is scaled by the scalar value
		Vector2D& operator *=(float _otherFloat)
		{
			x *= _otherFloat;
			y *= _otherFloat;
			return *this;
		}

		// assigns this Vector the value of this vector where each component is scaled by Vector Component Aligned with it.
		Vector2D operator*=(Vector2D _otherVector)
		{
			Vector2D tempVector = { x, y };
			x *= _otherVector.x;
			y *= _otherVector.y;
			return *this;
		}

		// returns a new Vector where each component is divided by the scalar value
		Vector2D operator /(float _otherFloat) const
		{
			Vector2D tempVector = { x, y };
			tempVector.x /= _otherFloat;
			tempVector.y /= _otherFloat;
			return tempVector;
		}

		// returns a new Vector where each component is scaled by the Vector Component Aligned with it.
		Vector2D operator/(Vector2D _otherVector) const
		{
			Vector2D tempVector = { x, y };
			tempVector.x /= _otherVector.x;
			tempVector.y /= _otherVector.y;
			return tempVector;
		}

		// returns a new Vector where each component is divided by the scalar value
		Vector2D& operator /=(float _otherFloat)
		{
			x /= _otherFloat;
			y /= _otherFloat;
			return *this;
		}

		// assigns this Vector the value of this vector where each component is scaled by Vector Component Aligned with it.
		Vector2D operator/=(Vector2D _otherVector)
		{
			Vector2D tempVector = { x, y };
			x /= _otherVector.x;
			y /= _otherVector.y;
			return *this;
		}

		// returns true if any component is NOT equal to the other in the other vector
		bool operator != (const Vector2D& _otherVector) const
		{
			return !(Equals(_otherVector));
		}

		friend std::ostream& operator<<(std::ostream& _stream, const Vector2D& _vector2D)
		{
			_stream << "x: " << _vector2D.x << ", y: " << _vector2D.y;
			return _stream;
		}

		float operator[](int _index)
		{
			return data[_index];
		}
		
		std::string ToString() const
		{
			return "x: " + std::to_string(x) + ", y: " + std::to_string(y);
		}

	};
		/**
			* Returns a new Vector where each component is scaled by the scalar value
			* @param scalar The scalar.
			* @param vector The Vector.
			* @return The scaled Vector.
			*/
	inline Vector2D operator*(float _scalar, const Vector2D& _vector)
	{
		return _vector * _scalar;
	}
}