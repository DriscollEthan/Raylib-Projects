#pragma once

#include "Utils.h"
#include "Vector3D.h"
#include "Vector2D.h"

namespace Driscoll
{
	struct Matrix3
	{
		/*
		 *		 c1 c2 c3
		 *	r1  1  2  3
		 *	r2  4	 5	6
		 *	r3  7  8  9
		 * 
		 * =========
		 * 
		 * m1 m4 m7
		 * m2 m5 m8
		 * m3 m6 m9
		 */


		union
		{
			struct
			{
				float m1, m2, m3, m4, m5, m6, m7, m8, m9;
			};

			float v[9];
			float mm[3][3];
			Vector3D axis[3];
		};

		/*
		 * Initializes members to the given values
		 *
		 * @param _inM1 Value for M1	| Default = 0
		 * @param _inM2 Value for M2	| Default = 0
		 * @param _inM3 Value for M3	| Default = 0
		 * @param _inM4 Value for M4	| Default = 0
		 * @param _inM5 Value for M5	| Default = 0
		 * @param _inM6 Value for M6	| Default = 0
		 * @param _inM7 Value for M7	| Default = 0
		 * @param _inM8 Value for M8	| Default = 0
		 * @param _inM9 Value for M9	| Default = 0
		 */
		Matrix3(float _inM1 = 0.0f, float _inM2 = 0.0f, float _inM3 = 0.0f, float _inM4 = 0.0f, float _inM5 = 0.0f, float _inM6 = 0.0f, float _inM7 = 0.0f, float _inM8 = 0.0f, float _inM9 = 0.0f)
		{
			m1 = _inM1;
			m2 = _inM2;
			m3 = _inM3;
			m4 = _inM4;
			m5 = _inM5;
			m6 = _inM6;
			m7 = _inM7;
			m8 = _inM8;
			m9 = _inM9;
		}

		//COPY CONSTRUCTOR
		Matrix3(const Matrix3& _otherMatrix3)
		{
			for (int i = 0; i < 9; ++i)
			{
				v[i] = _otherMatrix3.v[i];
			}
		}

		/*
		 * Initializes a matrix based on a 9-element array
		 *
		 * @details Does not perform bounds checking.
		 *
		 * @param inArr
		 */
		Matrix3(float* inArr)
		{
			for (int i = 0; i < 9; ++i)
			{
				v[i] = inArr[i];
			}
		}

		/*
		 * Initializes and returns an identity matrix.
		 *
		 * @return The identity matrix.
		 */
		static Matrix3 MakeIdentity()
		{
			return { 1.0f, 0, 0, 0, 1.0f, 0, 0, 0, 1.0f };
		}

		/*
			 * Multiplies this matrix against the given Matrix.
		 *
		 * Performs MATRIX multiplication, not just multiplying each member by
		 * the other.
			 *
			 * @param rhs The other matrix.
			 * @return The product of multiplying the 3x3 matrix by a 3x3.
			 */
		Matrix3 operator *(Matrix3 rhs) const
		{
			//Init Temp Matrix Var
			Matrix3 temp = *this;
			
			//Create Row Vector 3s from First Matrix
			Vector3D Row1 = { m1, m4, m7 };
			Vector3D Row2 = { m2, m5, m8 };
			Vector3D Row3 = { m3, m6, m9 };

			//Create Column Vector 3s from rhs Matrix
			Vector3D Column1 = { rhs.m1, rhs.m4, rhs.m7 };
			Vector3D Column2 = { rhs.m2, rhs.m5, rhs.m8 };
			Vector3D Column3 = { rhs.m3, rhs.m6, rhs.m9 };

			//Update the tempMaxtrix3 with Dot Prods from the Column and Rows
			temp.m1 = Row1.Dot(Column1);
			temp.m2 = Row1.Dot(Column2);
			temp.m3 = Row1.Dot(Column3);

			temp.m4 = Row2.Dot(Column1);
			temp.m5 = Row2.Dot(Column2);
			temp.m6 = Row2.Dot(Column3);

			temp.m7 = Row3.Dot(Column1);
			temp.m8 = Row3.Dot(Column2);
			temp.m9 = Row3.Dot(Column3);

			return temp;
		}

		/*
		 * Assigns and returns the result of this Matrix multiplied against the
		 * other Matrix.
		 *
		 * @param rhs The other Matrix.
		 * @return The reference to this Matrix after multiplication.
		 */
		Matrix3& operator *=(Matrix3 rhs)
		{
			(*this) = (*this) * rhs;

			return *this;
		}

		/*
		 * Multiplies this matrix against the given Vector3D, treating it like
		 * a 3x1 matrix.
		 *
		 * @param rhs The vector
		 * @return The product of multiplying the 3x3 by a 3x1
		 */
		Vector3D operator *(Vector3D rhs) const
		{
			Vector3D temp = {};

			//Create Row Vector 3s from First Matrix
			Vector3D Row1 = { m1, m4, m7 };
			Vector3D Row2 = { m2, m5, m8 };
			Vector3D Row3 = { m3, m6, m9 };

			temp.x = Row1.Dot(rhs);
			temp.y = Row2.Dot(rhs);
			temp.z = Row3.Dot(rhs);
			
			return temp;
		}

		/*
		 * Multiplies this matrix against the given Vector2D, treating it like
		 * a 3x1 matrix where its third element, normally Vector3D.z, is 1.0.
		 *
		 * @param rhs The vector
		 * @return The product of multiplying the 3x3 by a 3x1, then truncating
		 *		   it to a 2x1.
		 */
		Vector2D operator *(Vector2D rhs) const
		{
			Vector3D temp = {};

			//Create Row Vector 3s from First Matrix
			Vector3D Row1 = { m1, m4, m7 };
			Vector3D Row2 = { m2, m5, m8 };
			Vector3D Row3 = { m3, m6, m9 };

			temp.x = Row1.Dot(Vector3D(rhs, 1.0f));
			temp.y = Row2.Dot(Vector3D(rhs, 1.0f));
			temp.z = Row3.Dot(Vector3D(rhs, 1.0f));

			return Vector2D(temp.x, temp.y);
		}

		/*
		 * Returns true if every component is exactly equal to the other.
		 *
		 * See also: Equals() for approximate equality.
		 *
		 * @param rhs The other Matrix.
		 * @return True if equal, otherwise false.
		 */
		bool operator == (const Matrix3& rhs) const
		{
			return Equals(rhs);
		}

		/*
		 * Returns true if any component is not exactly equal to the other.
		 *
		 * @param rhs The other Matrix.
		 * @return True if equal, otherwise false.
		 */
		bool operator != (const Matrix3& rhs) const
		{
			return Equals(rhs);
		}

		/*
		 * Returns true if every component is exactly equal to the other.
		 *
		 * @param rhs The other Matrix.
		 * @return True if equal, otherwise false.
		 */
		bool Equals(const Matrix3& rhs) const
		{
			for (int i = 0; i < 9; ++i)
			{
				if (v[i] != rhs.v[i])
				{
					return false;
				}
			}
			return true;
		}

		/*
		 * Returns true if every component is approximately equal to the other.
		 *
		 * @param rhs The other Matrix.
		 * @return True if equal, otherwise false.
		 */
		bool NearlyEquals(const Matrix3& rhs, float Tolerance = MAX_FLOAT_DELTA) const
		{
			for (int i = 0; i < 9; ++i)
			{
				//Get the difference between the values
				float temp = v[i] - rhs.v[i];
				//Get the absolute Value for an accurate comparison
				temp *= (temp < 0) ? -1 : 1;
				//Compare, and if one number is greater than the tolerance, the matrix must not be nearly equal.
				if (temp > Tolerance)
				{
					return false;
				}
			}
			//If we never leave early every element must be nearly equal to every element in the other matrix.
			return true;
		}

		/*
		 * Returns this as a formatted string.
		 *
		 * @return A comma separated Vector with its components.
		 */
		std::string ToString() const
		{
			return "m1: " + std::to_string(m1) + ", m4: " + std::to_string(m4) + ", m7: " + std::to_string(m7)
				+ "\nm2: " + std::to_string(m2) + ", m5: " + std::to_string(m5) + ", m8: " + std::to_string(m8)
				+ "\nm3: " + std::to_string(m3) + ", m6 : " + std::to_string(m6) + ", m7 : " + std::to_string(m9);
		}

		/*
		 * Transform Factory Functions
		 */

		 // Raylib 2D utilizes a left-handed coordinate system where:
		 // - x+ is RIGHT
		 // - y+ is DOWN

		 /*
			* Creates a translation matrix that translates on the given X and Y
			* axis.
			*
			* For use with 2-D math.
			*
			* @param x Amount to translate by on the X-axis.
			* @param y Amount to translate by on the Y-axis.

			* @return The translation matrix.
			*/
		static Matrix3 MakeTranslation(float x, float y);

		/*
		 * Creates a translation matrix that translates on the given X and Y
		 * axes. No translation on the Z-axis.
		 *
		 * For use with 2-D math.
		 *
		 * @param vec A Vector containing the amount to translate by on the X, Y, and Z axes.
		 * @return The translation matrix.
		 */
		static Matrix3 MakeTranslation(Vector2D vec);

		/*
		 * Creates a translation matrix that translates on the given X, Y, and
		 * Z-axes.
		 *
		 * For use with 3-D math.
		 *
		 * @param x Amount to translate by on the X-axis.
		 * @param y Amount to translate by on the Y-axis.
		 * @param z Amount to translate by on the Z-axis.
		 * @return The translation matrix.
		 */
		static Matrix3 MakeTranslation(float x, float y, float z);

		/*
		 * Creates a translation matrix that translates on the given X, Y, and
		 * Z-axes.
		 *
		 * For use with 3-D math.
		 *
		 * @param vec A Vector containing the amount to translate by on the X, Y, and Z axes.
		 * @return The translation matrix.
		 */
		static Matrix3 MakeTranslation(Vector3D vec);

		/*
		 * Creates a rotation matrix that rotates around the X-axis
		 *
		 * @param Rotation around the X-axis, expressed in radians.
		 * @return The rotation matrix.
		 */
		static Matrix3 MakeRotateX(float a);

		/*
		 * Creates a rotation matrix that rotates around the Y-axis
		 *
		 * @param Rotation around the Y-axis, expressed in radians.
		 * @return The rotation matrix.
		 */
		static Matrix3 MakeRotateY(float a);

		/*
		 * Creates a rotation matrix that rotates around the Z-axis
		 *
		 * @param Rotation around the Z-axis, expressed in radians.
		 * @return The rotation matrix.
		 */
		static Matrix3 MakeRotateZ(float a);

		/*
		 * Creates a rotation matrix that applies a pitch, yaw, roll rotation
		 *
		 * Combined in a pitch, then yaw, then roll.
		 *
		 * @param pitch Amount to pitch, expressed in radians.
		 * @param yaw	Amount to yaw, expressed in radians.
		 * @param roll	Amount to roll, expressed in radians.
		 * @return The rotation matrix.
		 */
		static Matrix3 MakeEuler(float pitch, float yaw, float roll);

		/*
		 * Creates a rotation matrix that applies a pitch, yaw, roll rotation
		 * expressed as the X, Y, and Z components of a Vector.
		 *
		 * @param rot Vector containing how much to pitch (X), yaw (Y), and roll (Z)
		 * @return The rotation matrix.
		 */
		static Matrix3 MakeEuler(Vector3D rot);

		/*
		 * Creates a scaling matrix that applies to the X and Y axes.
		 *
		 * The third column is reserved for translation.
		 *
		 * For use with 2D-maths.
		 *
		 * @param xScale Scalar for the X-axis.
		 * @param yScale Scalar for the Y-axis.
		 * @return The scaling matrix.
		 */
		static Matrix3 MakeScale(float xScale, float yScale);

		/*
		 * Creates a scaling matrix that applies to the X, Y, and Z axis with
		 * no homogeneous coordinates, not allowing for any translation.
		 *
		 * For use with 3D-maths.
		 *
		 * @param xScale Scalar for the X-axis.
		 * @param yScale Scalar for the Y-axis.
		 * @return The scaling matrix.
		 */
		static Matrix3 MakeScale(float xScale, float yScale, float zScale);

		/*
		 * Creates a scaling matrix that applies to the X, Y, and Z axis with
		 * no homogeneous coordinates, not allowing for any translation. The
		 * amount to scale by on each axis is expressed as the components of
		 * a Vector's X, Y, and Z.
		 *
		 * For use with 3D-maths.
		 *
		 * @param scale Scale factor expressed as a Vector.
		 * @return The scaling matrix.
		 */
		static Matrix3 MakeScale(Vector3D scale);

		/*
		 * OPTIONAL
		 */

		 /*
			* Transposes the matrix, swapping the values along the diagonal defined
			* as m1, m5, m9.
			*
			* In other words, it turns its columns into rows.
			*
			* @return The transposed matrix.
			*/
		Matrix3 Transposed() const;

		/*
		 * Accesses the matrix as though it were an array of floats in columns.
		 *
		 * @param dim The index (accessed by "columns").
		 * @return Returns a reference to the element at the requested index.
		 */
		float& operator [](int dim)
		{
			return v[dim];
		}

		/*
		 * Accesses the matrix as though it were an array of floats in columns.
		 *
		 * @param dim The index (accessed by "columns").
		 * @return Returns a const reference to the element at the requested index.
		 */
		const float& operator [](int dim) const
		{
			return v[dim];
		}

		/*
		 * Casts the matrix as though it were an array of floats in columns.
		 *
		 * @return Returns a float* pointing to the first element of the "array".
		 */
		operator float* ()
		{
			return &v[0];
		}

		/*
		 * Casts the matrix as though it were an array of floats in columns.
		 *
		 * @return Returns a const float* pointing to the first element of the "array".
		 */
		operator const float* () const
		{
			return &v[0];
		}
	};
}