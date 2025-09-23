#pragma once

#include <iostream>
#include <string>

#include "Vector2D.h"
#include "Utils.h"

namespace Driscoll
{
	struct Vector3D
	{
		union
		{
			struct
			{
				float x, y, z;
			};

			float data[3];
		};

		//CONSTRUCTORS

		/*
		 * Initializes members to the given values
		 *
		 * @param _x Value for x | Default = 0
		 * @param _x Value for y | Default = 0
		 * @param _z Value for z | Default = 0
		 */
		Vector3D(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		/*
		 * Initializes a Vector3, copying the X and Y elements from the given
		 * Vector2 object.
		 *
		 * The Z value will be zero by default or as specified.
		 *
		 * @param _vector2D The Vector2 whose X and Y will be copied. | Default = 0
		 */
		Vector3D(const Driscoll::Vector2D& _vector2D = {}, float _z = 0)
		{
			x = _vector2D.x;
			y = _vector2D.y;
			z = _z;
		}

		/*
		 * Copy Constructor
		 *
		 * @param _otherVector Will be used to copy values into this Vector.
		 */
		Vector3D(const Vector3D& _otherVector)
		{
			x = _otherVector.x;
			y = _otherVector.y;
			z = _otherVector.z;
		}

		//FUNCTIONS:

		/*
		 * Returns the magnitude of this Vector
		 *
		 * @return The magnitude of this Vector.
		 */
		float Magnitude() const
		{
			return sqrtf((x * x) + (y * y) + (z * z));
		}

		/*
		 * Returns the squared magnitude of this Vector
		 *
		 * @return The magnitude of this Vector.
		 */
		float MagnitudeSqr() const
		{
			return ((x * x) + (y * y) + (z * z));
		}

		/*
		 * Returns the dot product of these vectors.
		 *
		 * @param _otherVector The other Vector.
		 * @return The dot product of this Vector and the other.
		 */
		float Dot(const Vector3D& _otherVector) const
		{
			return ((x * _otherVector.x) + (y * _otherVector.y) + (y + _otherVector.y));
		}

		/*
		 * Returns the dot product of these vectors.
		 *
		 * @param _firstVector The first operand.
		 * @param _secondVector The second operand.
		 * @return  The dot product of these Vectors.
		 */
		static float Dot(const Vector3D& _firstVector, const Vector3D& _secondVector)
		{
			return _firstVector.Dot(_secondVector);
		}

		/*
		 * Returns a Vector that is perpendicular to both this Vector and the other.
		 *
		 * @param _otherVector The other Vector.
		 * @details A Vector that is perpendicular to both this Vector and the other.
		 */
		Vector3D Cross(const Vector3D& _otherVector) const
		{
			Vector3D tempVector = *this;

			tempVector.x = (y * _otherVector.z) - (z * _otherVector.y);
			tempVector.y = (z * _otherVector.x) - (x * _otherVector.z);
			tempVector.y = (x * _otherVector.y) - (y * _otherVector.x);

			return tempVector;
		}

		/*
		 * Returns a Vector that is perpendicular to both Vectors.
		 *
		 * @param _firstVector The first Vector.
		 * @param _secondVector The second Vector.
		 * @details A Vector that is perpendicular to both Vectors.
		 */
		static Vector3D Cross(const Vector3D& _firstVector, const Vector3D& _secondVector)
		{
			return _firstVector.Cross(_secondVector);
		}

		/*
		 * Normalises this vector, modifying its length to be 1 while retaining the same direction.
		 *
		 * @details Does NOT check for zero-length vectors, which are invalid to normalise.
		 *
		 * See also: SafeNormalise().
		 */
		void Normalise()
		{
			float mag = this->Magnitude();

			x /= mag;
			y /= mag;
			z /= mag;

			return;
		}

		/*
		 * Safely normalises this vector, modifying its length to be 1 while retaining the same direction
		 * unless its length is zero, in which case its members will be set to zero.
		 *
		 * @details Does NOT check for zero-length vectors, which are invalid to normalise.
		 *
		 * See also: SafeNormalise().
		 */
		void SafeNormalise()
		{
			if (this->Magnitude() != 0)
			{
				Normalise();
			}
			return;
		}

		/*
		 * Returns a normalized copy of this vector.
		 *
		 * See also: SafeNormalised()
		 * @return A normalized copy.
		 */
		Vector3D Normalised() const
		{
			Vector3D tempVector = *this;
			tempVector.Normalise();

			return tempVector;
		}

		/*
		 * Returns a normalized copy of this vector or returns it as-is if too small to n
		 *
		 * @return A normalized copy if possible.
		 */
		Vector3D SafeNormalised() const
		{
			Vector3D tempVector = *this;
			tempVector.SafeNormalise();

			return tempVector;
		}

		/*
		 * Returns the Absolute Values for the Vector3D
		 *
		 * @return A Vector3D copy if possible.
		 */
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
			if (z < 0)
			{
				z *= -1;
			}

			return *this;
		}

		/*
		 * Returns true if every component is approximately equal to the other in the other vector
		 *
		 * @param _otherVector The other Vector.
		 * @param _tolerance The maximum difference between any component being compared.
		 * @return True if approximately equal, otherwise false.
		 */
		bool NearlyEquals(const Vector3D& _otherVector, float _tolerance = MAX_FLOAT_DELTA) const
		{
			Vector3D distance = { x - _otherVector.x, y - _otherVector.y, z - _otherVector.z };
			distance.Absolute();

			return ((distance.x < _tolerance) && (distance.y < _tolerance) && (distance.z < _tolerance));
		}

		/*
		 * Returns true if every component is exactly equal to the other in the other vector
		 *
		 * @param _otherVector The other Vector.
		 * @return True if exactly equal, otherwise false.
		 */
		bool Equals(const Vector3D& _otherVector) const
		{
			return (x == _otherVector.x && y == _otherVector.y && z == _otherVector.z);
		}

		/*
		 * Returns the distance between two Points.
		 *
		 * @details This Vector is one of those Points.
		 * @param _otherVector The other Point.
		 * @return The distance between those points.
		 */
		float Distance(const Vector3D& _otherVector) const
		{
			return (*this - _otherVector).Magnitude();
		}

		/*
		 * Returns the squared distance between two Points.
		 *
		 * @details This Vector is one of those Points.
		 * @param _otherVector The other Point.
		 * @return The squared distance between those points.
		 */
		float DistanceSqr(const Vector3D& _otherVector) const
		{
			return (*this - _otherVector).MagnitudeSqr();
		}

		/*
		 * Returns the distance between two Points.
		 *
		 * @param _start A Point.
		 * @param _end The other Point.
		 * @return The distance between those points.
		 */
		static float Distance(const Vector3D& _firstVector, const Vector3D& _secondVector)
		{
			return _firstVector.Distance(_secondVector);
		}

		/*
		 * Returns the squared distance between two Points.
		 *
		 * @param _start A Point.
		 * @param _end The other Point.
		 * @return The distance between those points.
		 */
		static float DistanceSqr(const Vector3D& _firstVector, const Vector3D& _secondVector)
		{
			return _firstVector.DistanceSqr(_secondVector);
		}

		/*
		 * Returns the acute angle between two Points expressed in Radians.
		 *
		 * @param _otherVector The other Point.
		 * @return The acute angle between those points.
		 */
		float AngleBetween(const Vector3D& _otherVector) const
		{
			return std::acosf(Dot(_otherVector) / (Magnitude() * _otherVector.Magnitude()));
		}

		/*
		 * Returns this Vector as a formatted string.
		 *
		 * @return A comma separated Vector with its components.
		 */
		std::string ToString() const
		{
			return "x: " + std::to_string(x) + ", y: " + std::to_string(y) + ", z: " + std::to_string(z);
		}

		//OPERATORS:

		/*
		 * Returns a Vector containing the sum of each component added to
		 * the other vector's component.
		 *
		 * @param _otherVector The other component.
		 * @return The Vector containing the sums of the components.
		 */
		Vector3D operator +(const Vector3D& _otherVector) const
		{
			Vector3D temp = *this;
			temp.x += _otherVector.x;
			temp.y += _otherVector.y;
			temp.z += _otherVector.z;

			return temp;
		}

		/*
		 * Assigns and returns the result of this Vector added to the other
		 * Vector.
		 *
		 * @param _otherVector The other Vector.
		 * @return The reference to this Vector after addition.
		 */
		Vector3D& operator +=(const Vector3D& _otherVector)
		{
			x += _otherVector.x;
			y += _otherVector.y;
			z += _otherVector.z;

			return *this;
		}

		/*
		 * Returns a Vector containing the difference of each component when
		 * subtracted from the other vector's component.
		 *
		 * @param _otherVector The other component.
		 * @return The Vector containing the differences of the components.
		 */
		Vector3D operator -(const Vector3D& _otherVector) const
		{
			Vector3D temp = *this;
			temp.x -= _otherVector.x;
			temp.y -= _otherVector.y;
			temp.z -= _otherVector.z;

			return temp;
		}

		/*
		 * Returns a Vector containing the difference of each component when
		 * subtracted from the other vector's component.
		 *
		 * @param _otherVector The other component.
		 * @return The Vector containing the differences of the components.
		 */
		Vector3D& operator -=(const Vector3D& _otherVector)
		{
			x -= _otherVector.x;
			y -= _otherVector.y;
			z -= _otherVector.z;

			return *this;
		}

		/*
		 * Returns a new Vector where each component is scaled by the scalar value
		 *
		 * @param _otherFloat The scalar.
		 * @return The scaled Vector.
		 */
		Vector3D operator *(float _otherFloat) const
		{
			Vector3D temp = *this;
			temp.x *= _otherFloat;
			temp.y *= _otherFloat;
			temp.z *= _otherFloat;

			return temp;
		}

		/*
		 * Assigns and returns this Vector scaled by the scalar value.
		 *
		 * @param _otherFloat The scalar.
		 * @return Reference to this Vector after scaling.
		 */
		Vector3D& operator *=(float _otherFloat)
		{
			x *= _otherFloat;
			y *= _otherFloat;
			z *= _otherFloat;

			return *this;
		}

		/* @note: (float * Vector3) implemented as a free-function below */

		/*
		 * Returns a new Vector where each component is divided by the value
		 *
		 * @param _otherFloat The divisor.
		 * @return The Vector after division.
		 */
		Vector3D operator /(float _otherFloat) const
		{
			Vector3D temp = *this;
			temp.x /= _otherFloat;
			temp.y /= _otherFloat;
			temp.z /= _otherFloat;

			return temp;
		}

		/*
		 * Assigns and returns this Vector after dividing its components.
		 *
		 * @param _otherFloat The divisor.
		 * @return Reference to this Vector after division.
		 */
		Vector3D operator /=(float _otherFloat)
		{
			x /= _otherFloat;
			y /= _otherFloat;
			z /= _otherFloat;

			return *this;
		}

		/*
		 * Returns true if every component is equal to the other in the other vector
		 *
		 * See also: Equals() for approximate equality.
		 * @param _otherVector The other Vector.
		 * @return True if equal, otherwise false.
		 */
		bool operator == (const Vector3D& _otherVector) const
		{
			return Equals(_otherVector);
		}

		/*
		 * Returns true if any component is NOT equal to the other in the other vector
		 *
		 * @param _otherVector The other Vector.
		 * @return True if inequal, otherwise false.
		 */
		bool operator != (const Vector3D& _otherVector) const
		{
			return !Equals(_otherVector);
		}

  };

	/**
	 * Returns a new Vector where each component is scaled by the scalar value
	 * @param _scalar The scalar.
	 * @param _vector The Vector.
	 * @return The scaled Vector.
	 */
	inline Vector3D operator*(float _scalar, const Vector3D& _vector)
	{
		return _vector * _scalar;
	}

}